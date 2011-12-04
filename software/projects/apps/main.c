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
#include "lm35.h"

uint8_t get_device_src(struct data_t *data) {
	return data->buf[-2];
}

uint8_t get_device_dst(struct data_t *data) {
	return data->buf[-1];
}

uint8_t get_node_src(struct data_t *data) {
	return data->packet[0];
}

void set_devices(struct data_t *data, uint8_t device_src, uint8_t device_dst) {
	data->buf[0] = device_src;
	data->buf[1] = device_dst;
}

void delay_1s() {
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
}

volatile uint8_t wake_me_up=0;

int8_t const_read(struct data_t *data) {
	uart_putstr_P(PSTR("const_read()\r\n"));
	if (data->remaining_len < 2) return -1;
	return set_data_int16(data,42);
}

/* This device get a string : "helloworld" and write
   what he get on the uart */
int8_t text_get(struct data_t *data) {
	char *text = "hello";
	uint8_t len = strlen(text);
	uart_putstr_P(PSTR("text_get()\r\n"));
	if (data->remaining_len < (len+2)) return -1;	/* Not enough room */
	
	return set_data_string(data,text,len);
}

uint16_t text_set(struct data_t *data) {
	uint8_t xx;
	char buf[4];

	/* Source node */
	xx = get_node_src(data);
	itoa(xx,buf,10);
	uart_putstr(buf);
	uart_putstr_P(PSTR(","));
	/* Source device */
	xx = get_device_src(data);
	itoa(xx,buf,10);
	uart_putstr(buf);
	uart_putstr_P(PSTR(","));
	/* Data type */
	xx = get_data_type(data);
	itoa(xx,buf,10);
	uart_putstr(buf);
	uart_putstr_P(PSTR(","));
	/* Datas */
	/* XXX */

	uart_putstr_P(PSTR("\r\n"));
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

/* Button */
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

// XXX: Theses structures belong to PROGMEM ...
const lm35_cfg_s lm35_cfg = {2};

const application_t applications[4] = {
// {lm35_init,lm35_read,NULL,(void*)&lm35_cfg},
 {NULL,const_read,NULL,NULL},
 {NULL,led_get,led_set,NULL},
 {button_init,button_read,NULL,NULL},
 {NULL,text_get,text_set,NULL},
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

		TCNT1 = 0;
	}

	// Asynchronous events
	if (wake_me_up > 0) {
		//send_data_to_peers_for_device(wake_me_up);
		wake_me_up = 0;
	}
 }
}
