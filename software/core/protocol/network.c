#include <avr/io.h>
#include <string.h>
#include "network.h"
#include "avr_compat.h"
#include "rfm12.h"
#include "config.h"
#include "ping.h"

#include "uart.h"

#include "bugOne.h"

static uint16_t counter = 0;

static struct packet_t packet;

#define DEBUG

void send(uint8_t dst, uint8_t type, struct packet_t *packet) {
	counter++;
	packet->network->src=config.address;
	packet->network->dst=dst;
	packet->network->hop=0;
	packet->network->type=type;
	packet->network->count=counter;
	//memcpy(network.payload,payload,size);
#ifdef DEBUG
	uart_putstr_P(PSTR("Sending\r\n"));
	uart_hexdump((char*)packet->network,BUGONE_PACKET_SIZE);
#endif
	rfm12_start_tx(0,BUGONE_PACKET_SIZE);
}

struct packet_t *get_tx_packet() {
	memset(rf_tx_buffer.buffer,0,sizeof(rf_tx_buffer.buffer));
	packet.network=(struct network_t*)rf_tx_buffer.buffer;
	packet.payload=rf_tx_buffer.buffer+sizeof(struct network_t);
	return &packet;
}


#if !(RFM12_TRANSMIT_ONLY)    
uint8_t recv(char* buf) {
#ifdef DEBUG
	uart_putstr_P(PSTR("Receiving\r\n"));
	uart_hexdump(buf,BUGONE_PACKET_SIZE);
#endif
	/* Now, we manipulate a packet_t structure to access received packet */
	struct packet_t packet;
	packet.network=(struct network_t*)buf;
	packet.payload=buf+sizeof(struct network_t);

	if ((packet.network->dst != config.address) && (packet.network->hop!=config.address)) {
		// This is not for us
		rfm12_rx_clear();
		return 0;
	}
	if ((packet.network->dst != config.address) && (packet.network->hop==config.address)) {
		// Forward this packet
		packet.network->hop=0;
		rfm12_tx(BUGONE_PACKET_SIZE,0,buf);
	}
	if (packet.network->type==HELLO) {
		// TODO
	}
	if (packet.network->type==PING) {
		recv_ping(&packet);
	}
	if (packet.network->type==PONG) {
		recv_pong();
	}
	if (packet.network->type==GET) {
		recv_get(&packet);
	}
	if (packet.network->type==SET) {
		recv_set(&packet);
	}
#if defined(BUGONE_HAS_CONFIG) && BUGONE_HAS_CONFIG
	if (packet.network->type==GET_CONFIG) {
		recv_get_config(&packet);
	}
#endif
	rfm12_rx_clear();
	return 0;
}
#endif 

uint8_t get_remaining_length(struct packet_t packet) {
	return (char*)packet.network+BUGONE_PACKET_SIZE-packet.payload;
}
