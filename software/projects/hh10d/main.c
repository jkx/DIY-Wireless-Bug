#include "bugOne.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include <avr/eeprom.h>

#include "avr_compat.h"
#include "rfm12.h"
#include "uart.h"
#include "config.h"

#include "apps.h"
#include "value.h"
#include "hh10d.h"
#include "led.h"
#include "const.h"
#include "button.h"

uint8_t get_node_src(struct data_t *data) {
	return data->packet[0];
}

volatile uint8_t wake_me_up=0;
volatile uint8_t seconds = 0;

void timer1_init() {
	// Set interrupt CTC mode. Every second (prescaler 1024 at 8MHz)
	TCCR1B |= (1 << WGM12);
  	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt 
	OCR1A = 7812;
	// Set timer 1 prescaler
	TCCR1B |= ((1 << CS10) | (1 << CS12)); // Set up timer at Fcpu/1024
}

ISR(TIMER1_COMPA_vect) {
	seconds++;
	toggle_output(LED2);
    	uart_putc('.');
	hh10d_freq();
}

// XXX: Theses structures belong to PROGMEM ...

const application_t applications[4] = {
 {NULL,const_read,NULL,NULL},
 {NULL,led_get,led_set,NULL},
 {button_init,button_read,NULL,NULL},
// {NULL,text_get,text_set,NULL},
 {hh10d_init,hh10d_read,NULL,NULL},
};

int main ( void )
{
  uint8_t *bufcontents;
  uint16_t ticker = 0;
  int16_t value;
  uint8_t i;
  char buf[28];

  bugone_init(applications);

  while (1) {
  	// RFM12 managment
	rfm12_tick();
	if (rfm12_rx_status() == STATUS_COMPLETE) {
		bufcontents=rfm12_rx_buffer();
		recv(bufcontents);
	}

	// Every minutes
	if (seconds > 20) {
		struct data_t data;
		int8_t len;
        	uart_putstr_P(PSTR("\r\n"));
		data.remaining_len=26;
		data.buf=buf;
		data.packet=buf;
		for (i=0 ; i < (sizeof(applications)/sizeof(*applications)) ; i++) {
    			uart_putstr_P(PSTR("#"));
			if (applications[i].get == NULL) { continue; }
			set_devices(&data,i,42);
			data.buf+=2;
			data.remaining_len-=2;
			len=applications[i].get(&data);
			if (len > 0) {
				data.remaining_len-=len;
				data.buf+=len;
			}
		}
		send(0xFF,6,buf,26);
		seconds=0;
	}

	// Asynchronous events
	if (wake_me_up > 0) {
		struct data_t data;
		int8_t len;
	        uart_putstr_P(PSTR("\r\n"));
		data.remaining_len=26;
		data.buf=buf;
		data.packet=buf;
		set_devices(&data,wake_me_up,42);
		data.buf+=2;
		data.remaining_len-=2;
		len=applications[wake_me_up].get(&data);
		send(0xFF,6,buf,26);

		wake_me_up = 0;
	}
 }
}
