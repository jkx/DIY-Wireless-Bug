#ifndef NETWORK_H
#define NETWORK_H

#define HELLO 1
#define PING 2
#define PONG 3
#define GET  4
#define SET  5
#define VALUE 6
#define SLEEP 7

struct hello_t {
	uint8_t	address;
	uint8_t	dest;
	uint8_t	cost;
};

struct pong_t {
	uint8_t version;
	uint8_t devices;
	uint32_t uptime;
};

struct network_t {
	uint8_t	src;
	uint8_t	dst;
	uint8_t	hop;
	uint8_t	type;
	uint16_t count;
};

struct packet_t {
	struct network_t* network;
	char* payload;
};

struct route_t {
	uint8_t dst;
	uint8_t hop;
	uint8_t cost;
};

struct packet_t *get_tx_packet();
void send(uint8_t dst, uint8_t type, struct packet_t *packet);
uint8_t recv(char* payload);

#include "config.h"

#endif
