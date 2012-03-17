#include "bugOne.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "avr_compat.h"
#include "rfm12.h"

#include "apps.h"
#include "config.h"

void delay_1s() {
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
}

void timer1_init() {
	// Set interrupt CTC mode. Every second (prescaler 1024 at 8MHz)
	TCCR1B |= (1 << WGM12);
  	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt 
	OCR1A = 7812;
	// Set timer 1 prescaler
	TCCR1B |= ((1 << CS10) | (1 << CS12)); // Set up timer at Fcpu/1024
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
                uart_putc('*');
		if (applications[i].init == NULL) { continue; }
		applications[i].init(applications[i].cfg);
	}

	timer1_init();

	sei();

	uart_putstr_P(PSTR("AVR init complete\r\n"));
	//clr_output(LED1);
	//clr_output(LED2);
}

extern application_t applications[];

volatile uint8_t wake_me_up=0;
volatile uint8_t seconds = 0;

ISR(TIMER1_COMPA_vect) {
	seconds++;
	toggle_output(LED2);
    	uart_putc('.');
}

int main ( void )
{
  uint8_t *bufcontents;
  uint8_t i;
  uint8_t nb_devices=0;
  application_t *app=applications;

  /* Count how many devices are declared */
  while (!((app->init == NULL) && 
              (app->get == NULL) && 
              (app->set == NULL) && 
              (app->cfg == NULL))) { 
      nb_devices++;
      app++;
  }

  bugone_init(applications,nb_devices);

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
                application_t *application;
		int8_t len;
        	uart_putstr_P(PSTR("\r\n"));
                i=0;
                while ( (application = get_app(i)) != NULL) {
                        i++;
    			uart_putstr_P(PSTR("#"));
			if (application->get == NULL) { continue; }
			set_devices(packet,i,0x29);
			len=application->get(packet);
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
