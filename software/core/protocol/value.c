#include <avr/io.h>
#include <string.h>
#include "network.h"
#include "avr_compat.h"
#include "rfm12.h"
#include "config.h"

#include "value.h"
#include "uart.h"

struct value_t {
	uint8_t sensor;
	int16_t value;
	int8_t  pow;
	uint8_t unit;
};

void send_value(uint8_t dst, int16_t value, int8_t pow, uint8_t unit) {
	uart_putstr_P(PSTR("send_value()\r\n"));

	struct value_t tvalue;
	tvalue.value = value;
	tvalue.pow = pow;
	tvalue.unit = unit;
	
	send(dst,VALUE,(char*)&tvalue,sizeof(struct value_t));
}

void start_value(struct ctx_t* ctx, uint8_t dst, char* buf) {
	uart_putstr_P(PSTR("start_value()\r\n"));
	ctx->dst = dst;
	ctx->buf = buf;
	ctx->cursor = buf;
}

void add_value(struct ctx_t* ctx, int16_t value, int8_t pow, uint8_t unit) {
	uart_putstr_P(PSTR("add_value()\r\n"));
	/* Do we have enough room for another value in the current packet */
	/* If not, we have to send it first */
	if ((ctx->cursor - ctx->buf + sizeof(struct value_t)) > 28) {
		end_value(ctx);
	}
	
	struct value_t tvalue;
	tvalue.value = value;
	tvalue.pow = pow;
	tvalue.unit = unit;

	memcpy(ctx->cursor,&tvalue,sizeof(struct value_t));
	ctx->cursor += sizeof(struct value_t);
}

void end_value(struct ctx_t* ctx) {
	uart_putstr_P(PSTR("end_value()\r\n"));
	send(ctx->dst,VALUE,ctx->buf,28);
	ctx->cursor = ctx->buf;
}
