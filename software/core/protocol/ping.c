#include <avr/io.h>
#include <string.h>
#include "network.h"
#include "avr_compat.h"
#include "rfm12.h"
#include "config.h"

#include "uart.h"

void recv_ping(char* payload) {
	struct network_t* network=(struct network_t*)payload;
	send(network->src,PONG,(char*)"pong",4);
}

void send_ping(uint8_t dst) {
	uart_putstr_P(PSTR("ping()\r\n"));
	send(dst,PING,(char*)"ping",4);
}

void recv_pong() {
	uart_putstr_P(PSTR("pong()\r\n"));
}
