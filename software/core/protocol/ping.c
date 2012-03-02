#include <avr/io.h>
#include <string.h>
#include "network.h"
#include "avr_compat.h"
#include "rfm12.h"
#include "config.h"

#include "uart.h"

void recv_ping(struct packet_t* packet) {
	struct packet_t *send_packet=get_tx_packet();
	struct pong_t *pong=(struct pong_t*)send_packet->payload;
	pong->version=FWVERSION;
	pong->devices=2;
	pong->uptime=0xBABE;
	send(packet->network->src,PONG,send_packet);
}

void send_ping(uint8_t dst) {
	uart_putstr_P(PSTR("ping()\r\n"));
	//send(dst,PING,(char*)"ping",4);
}

void recv_pong() {
	uart_putstr_P(PSTR("pong()\r\n"));
}
