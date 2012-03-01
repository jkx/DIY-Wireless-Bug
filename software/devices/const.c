#include "bugOne.h"
#include <avr/pgmspace.h>
#include "const.h"

int8_t const_read(struct packet_t *packet) {
	uart_putstr_P(PSTR("const_read()\r\n"));
	//if (data->remaining_len < 2) return -1;
	return set_data_int16(packet,42);
}

