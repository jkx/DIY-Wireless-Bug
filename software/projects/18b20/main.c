#include "bugOne.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include <avr/eeprom.h>

#include "avr_compat.h"
#include "rfm12.h"
#include "uart.h"
#include "config.h"

#include "apps.h"
#include "value.h"

#include "enc28j60.h"
#include "ip_arp_udp_tcp.h"
#include "net.h"

#include "led.h"
#include "const.h"
#include "ds18x20.h"
#include "onewire.h"

volatile uint8_t wake_me_up=0;
volatile uint8_t seconds = 0;

// Mac address is BUGONE
static uint8_t bugone_mac[6] = {0x42,0x55,0x47,0x4F,0x4E,0x45};
static uint8_t bugone_ip[4] = {192,168,1,1};
static uint8_t computer_ip[4] = {192,168,1,2};

void timer1_init() {
	// Set interrupt CTC mode. Every second (prescaler 1024 at 8MHz)
	TCCR1B |= (1 << WGM12);
  	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt 
	OCR1A = 7812;
	// Set timer 1 prescaler
	TCCR1B |= ((1 << CS10) | (1 << CS12)); // Set up timer at Fcpu/1024
}

ISR(TIMER1_COMPA_vect) {
	seconds++;
	toggle_output(LED2);
    	uart_putc('.');
}

// XXX: Theses structures belong to PROGMEM ...

application_t applications[] = {
 {NULL,const_read,NULL,NULL},
 {NULL,led_get,led_set,NULL},
 {NULL,ds18x20_read,NULL,NULL},
};


#define BUFFER_SIZE 100
//static uint8_t buf_eth[BUFFER_SIZE+1];

int main ( void )
{
  uint8_t *bufcontents;
  uint16_t ticker = 0;
  int16_t value;
  uint8_t i;
  char buf[28];
  uint16_t plen;
  uint16_t dat_p;

  bugone_init(applications);
#if 0
	enc28j60Init(bugone_mac);
	init_ip_arp_udp_tcp(bugone_mac,bugone_ip,80);
	uart_putstr_P(PSTR("enc28j60 rev. "));
	rev = enc28j60getrev();
	itoa(rev,buf,10);
	uart_putstr(buf);
	uart_putstr_P(PSTR("\r\n"));
#endif


  while (1) {
  	// ENC28J60 managment
	//plen = enc28j60PacketReceive(BUFFER_SIZE, buf_eth);
	//buf_eth[BUFFER_SIZE]='\0';
	//dat_p=packetloop_icmp_tcp(buf_eth,plen);

  	// RFM12 managment
	rfm12_tick();
	if (rfm12_rx_status() == STATUS_COMPLETE) {
		bufcontents=rfm12_rx_buffer();
		// Mirror every received packet to the ethernet
		//send_udp(buf_eth,bufcontents,32,2000,computer_ip,3000);
		recv(bufcontents);
	}

	// Every minutes
	if (seconds > 20) {
		struct packet_t *packet = get_tx_packet();
		int8_t len;
        	uart_putstr_P(PSTR("\r\n"));
		for (i=0 ; i < (sizeof(applications)/sizeof(*applications)) ; i++) {
    			uart_putstr_P(PSTR("#"));
			if (applications[i].get == NULL) { continue; }
			set_devices(packet,i,0x29);
			len=applications[i].get(packet);
			if (len > 0) {
				//data.remaining_len-=len;
				//data.buf+=len;
			}
		}
		send(0xFF,6,packet);
		seconds=0;
	}

	// Asynchronous events
	if (wake_me_up > 0) {
		struct packet_t *packet = get_tx_packet();
		int8_t len;
	        uart_putstr_P(PSTR("\r\n"));
		set_devices(packet,wake_me_up,42);
		len=applications[wake_me_up].get(packet);
		send(0xFF,VALUE,packet);

		wake_me_up = 0;
	}
 }
}
