#include <avr/io.h>
#include <string.h>
#include "network.h"
#include "avr_compat.h"
#include "rfm12.h"
#include "config.h"

#include "uart.h"

struct value_t {
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
