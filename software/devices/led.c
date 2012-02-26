#include "bugOne.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "avr_compat.h"
#include "led.h"

/* Init on board LEDs */
void led_init() {
	drive(LED1);
	drive(LED2);

	set_output(LED1);
	set_output(LED2);
}

void led_set(struct data_t *data) {
	uart_putstr_P(PSTR("led_set()\r\n"));
	if (get_data_type(data)!='I') return;
	if (get_data_int16(data) == 0) {
		uart_putstr_P(PSTR("clr_led()\r\n"));
		clr_output(LED1);
	} else {
		uart_putstr_P(PSTR("set_led()\r\n"));
		set_output(LED1);
	}
}

int8_t led_get(struct data_t *data) {
	uart_putstr_P(PSTR("led_get()\r\n"));
	return set_data_int16(data,get_output(LED1));
}

