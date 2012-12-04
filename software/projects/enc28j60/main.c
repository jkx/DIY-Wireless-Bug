/* 

   A bugnet to ethernet bridge. Forward all bugnet traffic to the
   designated receiver.

   eeprom layout :
    0    : bugone node address (unused)
    1-6  : Mac address
    7-8  : UDP destination port
    9-73 : IP or hostname of receiver

- Documentation
- use mac as bugnet id


*/


#include "bugOne.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#include <avr/wdt.h>

#include "avr_compat.h"
#include "uart.h"
#include "config.h"

#include "enc28j60.h"
#include "ip_arp_udp_tcp.h"
#include "net.h"

#include "rfm12.h"

// Mac address is BUGONE
//static uint8_t bugone_mac[6] = { 0x42, 0x55, 0x47, 0x4F, 0x4E, 0x45 };

static uint8_t otherside_www_ip[4];	// dns will fill this
// My own IP (DHCP will provide a value for it):
static uint8_t myip[4] = { 0, 0, 0, 0 };

// Default gateway (DHCP will provide a value for it):
static uint8_t gwip[4] = { 0, 0, 0, 0 };

#define TRANS_NUM_GWMAC 1
static uint8_t gwmac[6];
#define TRANS_NUM_WEBMAC 2
static uint8_t otherside_www_gwmac[6];
// Netmask (DHCP will provide a value for it):
static uint8_t netmask[4];

extern uint8_t dnsip[4];

static int8_t processing_state = 0;
static uint8_t start_udp_client = 0;
extern uint8_t seconds;
#define MYUDPPORT 3000

#define BUFFER_SIZE 350
static uint8_t buf[BUFFER_SIZE + 1];

application_t applications[] = {
    {NULL, NULL, NULL, NULL}
};

// the __attribute__((unused)) is a gcc compiler directive to avoid warnings about unsed variables.
void
arpresolver_result_callback(uint8_t * ip
			    __attribute__ ((unused)),
			    uint8_t reference_number, uint8_t * mac)
{
    uint8_t i = 0;
    if (reference_number == TRANS_NUM_GWMAC) {
	// copy mac address over:
	while (i < 6) {
	    gwmac[i] = mac[i];
	    i++;
	}
    }
    if (reference_number == TRANS_NUM_WEBMAC) {
	// copy mac address over:
	while (i < 6) {
	    otherside_www_gwmac[i] = mac[i];
	    i++;
	}
    }
}

void print_ip(uint8_t * ip)
{
    char buf[4];
    itoa(*ip++, buf, 10);
    uart_putstr(buf);
    uart_putc('.');
    itoa(*ip++, buf, 10);
    uart_putstr(buf);
    uart_putc('.');
    itoa(*ip++, buf, 10);
    uart_putstr(buf);
    uart_putc('.');
    itoa(*ip++, buf, 10);
    uart_putstr(buf);
}

int main(void)
{
    uint8_t rev;
    uint16_t plen;
    uint16_t i = 0;
    uint16_t dat_p;

    wdt_disable();

    drive(LED1);
    drive(LED2);

    set_output(LED1);
    set_output(LED2);

    uart_init();
    bugone_init(applications);

    enc28j60Init(config.mac);

    uart_putstr_P(PSTR("AVR init complete\r\n"));

    uart_putstr_P(PSTR("enc28j60 rev. "));
    rev = enc28j60getrev();
    itoa(rev, buf, 10);
    uart_putstr(buf);
    uart_putstr_P(PSTR("\r\n"));

    uart_putstr(config.collector);

    uint8_t rval;

    // DHCP handling. Get the initial IP
    rval = 0;
    init_mac(config.mac);
    while (rval == 0) {
	plen = enc28j60PacketReceive(BUFFER_SIZE, buf);
	buf[BUFFER_SIZE] = '\0';
	rval =
	    packetloop_dhcp_initial_ip_assignment(buf, plen,
						  config.mac[5]);
    }
    // we have an IP:
    dhcp_get_my_ip(myip, netmask, gwip);
    client_ifconfig(myip, netmask);
    uart_putstr_P(PSTR("my IP is: "));
    print_ip(myip);
    uart_putstr_P(PSTR("gateway IP is: "));
    print_ip(gwip);
    uart_putstr_P(PSTR("DNS IP is: "));
    print_ip(dnsip);

    // we have a gateway.
    // find the mac address of the gateway (e.g your dsl router).
#define TRANS_NUM_GWMAC 1
    get_mac_with_arp(gwip, TRANS_NUM_GWMAC, &arpresolver_result_callback);
    while (get_mac_with_arp_wait()) {
	// to process the ARP reply we must call the packetloop
	plen = enc28j60PacketReceive(BUFFER_SIZE, buf);
	packetloop_arp_icmp_tcp(buf, plen);
    }

    while (1) {
	uint8_t *bufcontents;
	uint8_t i;

	i++;

	// RFM12 managment
	rfm12_poll();
	if (i > 100) {
	    rfm12_tick();
	    i = 0;
	}

	if (rfm12_rx_status() == STATUS_COMPLETE) {
	    bufcontents = rfm12_rx_buffer();
	    //recv(bufcontents);
	    toggle_output(LED1);
	    if (start_udp_client == 1) {
                uint8_t j;
		uart_putstr_P(PSTR("send UDP packet\r\n"));
                send_udp_prepare(buf, 2000, otherside_www_ip, config.udp_dstport, gwmac);
                // Put the mac address as a bugnet id
                for(j=0; j < 6; j++) {
                    buf[UDP_DATA_P+j]=config.mac[j];
                }
                for(j=0; j < BUGONE_PACKET_SIZE; j++) {
                    buf[UDP_DATA_P+6+j]=bufcontents[j];
                }
                send_udp_transmit(buf,BUGONE_PACKET_SIZE+sizeof(config.mac));
	    }
            rfm12_rx_clear();
	}

	// get the next new packet:
	plen = enc28j60PacketReceive(BUFFER_SIZE, buf);
	buf[BUFFER_SIZE] = '\0';
	// DHCP renew IP:
	plen = packetloop_dhcp_renewhandler(buf, plen);	// for this to work you have to call dhcp_6sec_tick() every 6 sec
	dat_p = packetloop_arp_icmp_tcp(buf, plen);
	if (plen == 0) {
	    // we are idle here
	    if (processing_state == 0) {
		if (!enc28j60linkup())
		    continue;	// only for dnslkup_request we have to check if the link is up. 
		seconds = 0;
		processing_state = 1;
		dnslkup_request(buf, config.collector, gwmac);
		continue;
	    }
	    if (processing_state == 1 && dnslkup_haveanswer()) {
		dnslkup_get_ip(otherside_www_ip);
		uart_putstr_P(PSTR("server IP is: "));
		print_ip(otherside_www_ip);
		processing_state = 2;
	    }
	    if (processing_state == 2) {
		if (route_via_gw(otherside_www_ip)) {
		    // otherside_www_ip is behind the GW
		    i = 0;
		    while (i < 6) {
			otherside_www_gwmac[i] = gwmac[i];
			i++;
		    }
		    processing_state = 4;
		} else {
		    // the web server we want to contact is on the local lan. find the mac:

		    get_mac_with_arp(otherside_www_ip, TRANS_NUM_WEBMAC,
				     &arpresolver_result_callback);
		    processing_state = 3;
		}
		continue;
	    }
	    if (processing_state == 3 && get_mac_with_arp_wait() == 0) {
		// we have otherside_www_gwmac
		processing_state = 4;
	    }
	    if (processing_state == 4) {
		processing_state = 5;
		// we are ready to upload the first measurement data after startup:
		if (start_udp_client == 0)
		    start_udp_client = 1;

	    }
	    if (processing_state == 1) {
		// retry every 20 sec if dns-lookup failed:
		if (seconds > 20) {
		    processing_state = 0;
		}
		// don't try to use web client before
		// we have a result of dns-lookup
		continue;
	    }
	    //----------
	}


	if (dat_p == 0) {	// plen!=0
	    // check for incomming messages not processed
	    // as part of packetloop_arp_icmp_tcp, e.g udp messages
	    udp_client_check_for_dns_answer(buf, plen);
	    continue;
	}

	if (seconds > 6) {
	    dhcp_6sec_tick();
	    seconds = 0;
	}
    }
}
