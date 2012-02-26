#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "bugOne.h"
#include "apps.h"
#include "config.h"

/* Initialise board */
void bugone_init(application_t* applications) {
	char buf[16];
	uint8_t i;

	led_init();
  	delay_1s();
	uart_init();
	rfm12_init();
	config_init();
	set_apps(applications,sizeof(applications)/sizeof(*applications));

	uart_putstr_P(PSTR("Firmware version "));
	uart_putstr_P(PSTR(FWVERSION));
	uart_putstr_P(PSTR("\r\n"));

	uart_putstr_P(PSTR("Node address : "));
	itoa(config.address,buf,10);
	uart_putstr(buf);
	uart_putstr_P(PSTR("\r\n"));

	for (i=0 ; i < (sizeof(applications)/sizeof(*applications)); i++) {
		if (applications[i].init == NULL) { continue; }
		applications[i].init(applications[i].cfg);
	}

	timer1_init();

	sei();

	uart_putstr_P(PSTR("AVR init complete\r\n"));
	//clr_output(LED1);
	//clr_output(LED2);
}
