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

#include "led.h"
#include "const.h"
#include "lm35.h"

volatile uint8_t wake_me_up=0;
volatile uint8_t seconds = 0;

void timer1_init() {
	// Set timer 1 prescaler
	TCCR1B |= ((1 << CS10) | (1 << CS12)); // Set up timer at Fcpu/1024
}

// XXX: Theses structures belong to PROGMEM ...
const lm35_cfg_s lm35_cfg = {3};

application_t applications[] = {
 {NULL,const_read,NULL,NULL},
 {NULL,led_get,led_set,NULL},
 //{button_init,button_read,NULL,NULL},
 {lm35_init,lm35_read,NULL,(void*)&lm35_cfg},
};

int main ( void )
{
  uint8_t *bufcontents;
  uint8_t i;
  char buf[16];

  uint16_t temperature;

  bugone_init(applications,3);

  while (1) {
  	// RFM12 managment
	rfm12_tick();
	if (rfm12_rx_status() == STATUS_COMPLETE) {
		bufcontents=rfm12_rx_buffer();
		recv(bufcontents);
	}

	// Every minutes
	if (seconds > 20) {
		struct packet_t *packet = get_tx_packet();
		int8_t len;
        	uart_putstr_P(PSTR("\r\n"));
		for (i=0 ; i < (sizeof(applications)/sizeof(*applications)) ; i++) {
    			uart_putstr_P(PSTR("#"));
			if (applications[i].get == NULL) { continue; }
			set_devices(packet,i,0x29);
			len=applications[i].get(packet);
			if (len > 0) {
				//data.remaining_len-=len;
				//data.buf+=len;
			}
		}
		send(0xFF,6,packet);
		seconds=0;
	}

	// Asynchronous events
	if (wake_me_up > 0) {
		struct packet_t *packet = get_tx_packet();
		int8_t len;
	        uart_putstr_P(PSTR("\r\n"));
		set_devices(packet,wake_me_up,42);
		len=applications[wake_me_up].get(packet);
		send(0xFF,VALUE,packet);

		wake_me_up = 0;
	}
 }
}
