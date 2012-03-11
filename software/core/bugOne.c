#include "bugOne.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "apps.h"
#include "config.h"

void delay_1s() {
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
}

/* Initialise board */
void bugone_init(application_t* applications, uint8_t nb_devices) {
	char buf[16];
	uint8_t i;

	led_init();
	uart_init();
	rfm12_init();
	config_init();
	set_apps(applications,nb_devices);

	uart_putstr_P(PSTR("Firmware version "));
	uart_putstr_P(PSTR(FWVERSION_STR));
	uart_putstr_P(PSTR("\r\n"));

	uart_putstr_P(PSTR("Node address : "));
	itoa(config.address,buf,10);
	uart_putstr(buf);
	uart_putstr_P(PSTR("\r\n"));

	for (i=0 ; i < nb_devices; i++) {
		if (applications[i].init == NULL) { continue; }
		applications[i].init(applications[i].cfg);
	}

	timer1_init();

	sei();

	uart_putstr_P(PSTR("AVR init complete\r\n"));
	//clr_output(LED1);
	//clr_output(LED2);
}
