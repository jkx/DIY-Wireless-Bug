#include "bugOne.h"
#include <avr/pgmspace.h>
#include "const.h"

int8_t const_read(struct data_t *data) {
	uart_putstr_P(PSTR("const_read()\r\n"));
	if (data->remaining_len < 2) return -1;
	return set_data_int16(data,42);
}

