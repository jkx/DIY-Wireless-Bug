#include <avr/interrupt.h>
#include "button.h"

extern uint8_t wake_me_up;

#define BUTTON1 D,4
void button_init(void* cfg) {
	// Button is connected to PD4 / PCINT20
	PCMSK2 |= (1 << PCINT20);
	PCICR |= (1 << PCIE2);
}

ISR (PCINT2_vect) {
	uart_putstr_P(PSTR("ISR\r\n"));
	wake_me_up = 2;
}

int8_t button_read(struct data_t *data) {
	uart_putstr_P(PSTR("button read\r\n"));
	set_data_int16(data,get_input(BUTTON1));
	return 3;
}

