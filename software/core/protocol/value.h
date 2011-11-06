#ifndef VALUE_H
#define VALUE_H

#define UNIT_CELSIUS 1
#define UNIT_VOLT 2

// Send one value
void send_value(uint8_t dst, int16_t value, int8_t pow, uint8_t unit);

struct ctx_t {
	uint8_t dst;
	char *buf;
	char *cursor;
};

// send severals values in one packet
void start_value(struct ctx_t* ctx, uint8_t dst, char* buf);
void add_value(struct ctx_t* ctx, int16_t value, int8_t pow, uint8_t unit);
void end_value(struct ctx_t* ctx);

#include "config.h"

#endif
