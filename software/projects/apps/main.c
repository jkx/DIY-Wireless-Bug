#include "bugOne.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <avr/sleep.h>
#include <stdlib.h>

#include "avr_compat.h"
#include "rfm12.h"
#include "uart.h"
#include "config.h"

#include "value.h"
#include "lm35.h"
#include "apps.h"

void delay_1s() {
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
}

int16_t const_read() {
	uart_putstr_P(PSTR("const_read()\r\n"));
	return 42;
}

void timer1_init() {
	// Set timer 1 prescaler
	TCCR1B |= ((1 << CS10) | (1 << CS12)); // Set up timer at Fcpu/1024
}

/* Init on board LEDs */
void led_init() {
	drive(LED1);
	drive(LED2);

	set_output(LED1);
	set_output(LED2);
}

void led_set(int16_t value) {
	uart_putstr_P(PSTR("led_set()\r\n"));
	if (value == 0) {
		uart_putstr_P(PSTR("clr_led()\r\n"));
		clr_output(LED1);
	} else {
		uart_putstr_P(PSTR("set_led()\r\n"));
		set_output(LED1);
	}
}

int16_t led_get() {
	uart_putstr_P(PSTR("led_get()\r\n"));
	return get_output(LED1);
}

// XXX: Theses structures belong to PROGMEM ...
const lm35_cfg_s lm35_cfg = {2};

const application_t applications[3] = {
 {lm35_init,lm35_read,NULL,(void*)&lm35_cfg},
 {NULL,const_read,NULL,NULL},
 {NULL,led_get,led_set,NULL},
};

/* Initialise board */
void bugone_init() {
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
	clr_output(LED1);
	clr_output(LED2);
}

int main ( void )
{
  uint8_t *bufcontents;
  uint16_t ticker = 0;
  int16_t value;
  uint8_t seconds = 0;
  uint8_t i;
  char buf[28];
  struct ctx_t ctx;

  bugone_init();

  while (1) {
  	// RFM12 managment
	rfm12_tick();
	if (rfm12_rx_status() == STATUS_COMPLETE) {
		bufcontents=rfm12_rx_buffer();
		recv(bufcontents);
	}

	// Every second
	if (TCNT1 >= 7812) {
		toggle_output(LED2);
		seconds++;

	    	uart_putstr_P(PSTR("."));
		// Every minutes
		if (seconds > 20) {
	        	uart_putstr_P(PSTR("\r\n"));
			start_value(&ctx,2,buf);
			for (i=0 ; i < (sizeof(applications)/sizeof(*applications)) ; i++) {
	    			uart_putstr_P(PSTR("#"));
				if (applications[i].get == NULL) { continue; }
				value=applications[i].get();
				add_value(&ctx,value,-1,0);
			}
			end_value(&ctx);
			seconds=0;
		}

		TCNT1 = 0;
	}
 }
}
