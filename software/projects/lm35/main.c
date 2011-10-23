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

void delay_1s() {
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
}

void timer1_init() {
	// Set timer 1 prescaler
	TCCR1B |= ((1 << CS10) | (1 << CS12)); // Set up timer at Fcpu/1024
}

int main ( void )
{
  uint8_t *bufcontents;
  uint16_t ticker = 0;
  char buf[16];

  uint16_t temperature;

  drive(LED1);
  drive(LED2);

  set_output(LED1);
  set_output(LED2);
	
  uart_init();
  timer1_init();
  lm35_init();

  delay_1s();
  
  uart_putstr_P(PSTR("Firmware version "));
  uart_putstr_P(PSTR(FWVERSION));
  uart_putstr_P(PSTR("\r\n"));

  config_init();

  uart_putstr_P(PSTR("Node address : "));
  itoa(config.address,buf,10);
  uart_putstr(buf);
  uart_putstr_P(PSTR("\r\n"));

  _delay_ms(250);
  rfm12_init();
  _delay_ms(250);

  sei();

  clr_output(LED1);
  clr_output(LED2);

  uart_putstr_P(PSTR("AVR init complete\r\n"));

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

		// Send temperature to node 0
  		uart_putstr_P(PSTR("Send temperature\r\n"));
		temperature = lm35_read();
		send_value(0,temperature,-1,UNIT_CELSIUS);

		TCNT1 = 0;
	}
 }
}
