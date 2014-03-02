#include "bugOne.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "avr_compat.h"
#include "button.h"

extern uint8_t send_flush;

#define BUTTON1 D,4
void button_init(void* cfg) {
	// Button is connected to PD4 / PCINT20
	PCMSK2 |= (1 << PCINT20);
	PCICR |= (1 << PCIE2);
}

ISR (PCINT2_vect) {
	uart_putstr_P(PSTR("ISR\r\n"));
	send_flush = 0;
}

int8_t button_read(struct packet_t *packet) {
	uart_putstr_P(PSTR("button read\r\n"));
	set_data_int16(packet,get_input(BUTTON1));
	return 3;
}

