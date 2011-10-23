#include <avr/io.h>
#include <string.h>
#include "network.h"
#include "avr_compat.h"
#include "rfm12.h"
#include "config.h"
#include "ping.h"

#include "uart.h"

static uint16_t counter = 0;

void send(uint8_t dst, uint8_t type, char* payload, uint8_t size) {
	struct network_t network;
	counter++;
	network.src=config.address;
	network.dst=dst;
	network.hop=0;
	network.type=type;
	network.count=counter;
	memcpy(network.payload,payload,size);
	rfm12_tx(32,0,(char*)&network);
}

uint8_t recv(char* payload) {
	struct network_t* network=(struct network_t*)payload;

	if ((network->dst != config.address) && (network->hop!=config.address)) {
		// This is not for us
		rfm12_rx_clear();
		return 0;
	}
	if ((network->dst != config.address) && (network->hop==config.address)) {
		// Forward this packet
		network->hop=0;
		rfm12_tx(32,0,payload);
	}
	if (network->type==HELLO) {
		// TODO
	}
	if (network->type==PING) {
		recv_ping(payload);
	}
	if (network->type==PONG) {
		recv_pong();
	}
	payload=network->payload;
	rfm12_rx_clear();
	return network->type;
}
