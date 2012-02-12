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
#include "ds18x20.h"
#include "onewire.h"

#include "enc28j60.h"
#include "ip_arp_udp_tcp.h"
#include "net.h"

uint8_t get_node_src(struct data_t *data) {
	return data->packet[0];
}

void delay_1s() {
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
}

volatile uint8_t wake_me_up=0;
volatile uint8_t seconds = 0;

// Mac address is BUGONE
static uint8_t bugone_mac[6] = {0x42,0x55,0x47,0x4F,0x4E,0x45};
static uint8_t bugone_ip[4] = {192,168,1,1};
static uint8_t computer_ip[4] = {192,168,1,2};

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

/*
ISR (PCINT2_vect) {
	uart_putstr_P(PSTR("ISR\r\n"));
	wake_me_up = 2;
}
*/

int8_t button_read(struct data_t *data) {
	uart_putstr_P(PSTR("button read\r\n"));
	set_data_int16(data,get_input(BUTTON1));
	return 3;
}

/* ds18x20 */
void ds18x20_init(void *cfg) {
	uint8_t diff,id;

	uart_putstr_P(PSTR("ds18x20 init\r\n"));

	ow_reset();

	diff=OW_SEARCH_FIRST;
	DS18X20_find_sensor(&diff, &id);

	if( diff == OW_PRESENCE_ERR ) {
		uart_putstr_P(PSTR("No Sensor found\r\n"));
		return;
	}

	uart_putstr_P(PSTR("ds18x20 init end\r\n"));

}

int8_t ds18x20_read(struct data_t *data) {
	uart_putstr_P(PSTR("ds18x20 read\r\n"));
	return 0;
}

// XXX: Theses structures belong to PROGMEM ...
//const lm35_cfg_s lm35_cfg = {3};

const application_t applications[4] = {
 {NULL,const_read,NULL,NULL},
 {NULL,led_get,led_set,NULL},
 {NULL,ds18x20_read,NULL,NULL},
 {NULL,button_read,NULL,NULL},
};

/* Initialise board */
void bugone_init() {
	char buf[16];
	uint8_t i;
	uint8_t rev;

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
#if 0
	enc28j60Init(bugone_mac);
	init_ip_arp_udp_tcp(bugone_mac,bugone_ip,80);
	uart_putstr_P(PSTR("enc28j60 rev. "));
	rev = enc28j60getrev();
	itoa(rev,buf,10);
	uart_putstr(buf);
	uart_putstr_P(PSTR("\r\n"));
#endif


	uart_putstr_P(PSTR("AVR init complete\r\n"));
	clr_output(LED1);
	clr_output(LED2);
}

#define BUFFER_SIZE 100
//static uint8_t buf_eth[BUFFER_SIZE+1];

int main ( void )
{
  uint8_t *bufcontents;
  uint16_t ticker = 0;
  int16_t value;
  uint8_t i;
  char buf[28];
  uint16_t plen;
  uint16_t dat_p;

  bugone_init();

  while (1) {
  	// ENC28J60 managment
	//plen = enc28j60PacketReceive(BUFFER_SIZE, buf_eth);
	//buf_eth[BUFFER_SIZE]='\0';
	//dat_p=packetloop_icmp_tcp(buf_eth,plen);

  	// RFM12 managment
	rfm12_tick();
	if (rfm12_rx_status() == STATUS_COMPLETE) {
		bufcontents=rfm12_rx_buffer();
		// Mirror every received packet to the ethernet
		//send_udp(buf_eth,bufcontents,32,2000,computer_ip,3000);
		recv(bufcontents);
	}

	// Every minutes
	if (seconds > 20) {
		struct data_t data;
		int8_t len;
        	uart_putstr_P(PSTR("\r\nsending devices values\r\n"));
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
