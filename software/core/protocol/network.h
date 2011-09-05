#ifndef NETWORK_H
#define NETWORK_H

#define HELLO 1
#define PING 2
#define PONG 3
#define DATA 10

struct hello_t {
	uint8_t	address;
	uint8_t	dest;
	uint8_t	cost;
};

struct {
} ping;

struct network_t {
	uint8_t	src;
	uint8_t	dst;
	uint8_t	hop;
	uint8_t	type;
	char payload[28];
};

struct route_t {
	uint8_t dst;
	uint8_t hop;
	uint8_t cost;
};

void send(uint8_t dst, uint8_t type, char* payload);
uint8_t recv(char* payload);

#include "config.h"

#endif
