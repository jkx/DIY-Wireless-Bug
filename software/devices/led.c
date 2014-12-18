/* 
   bugOne onboard led driver
   =========================
   LED1 is the power led, in normal operation it should be on,
   in power-down mode, it should only blink
   
   LED2 is the app led, feel free to use it
*/


#include "bugOne.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "avr_compat.h"
#include "led.h"

// Init on board LEDs
void led_init() {
	led_setup();
	set_output(LED1);
	set_output(LED2);

	delay_500ms();
	clr_output(LED2);
}

void led_set(struct packet_t *packet) {
	uart_putstr_P(PSTR("led_set()\r\n"));
	// XXX : WTF ??? if (get_data_type(packet)!=0x49) { uart_putstr_P(PSTR("not an integer")); return; }
	uart_putc(get_data_type(packet));
	if (get_data_int16(packet) == 0) {
		uart_putstr_P(PSTR("clr_led()\r\n"));
		clr_output(LED1);
	} else {
		uart_putstr_P(PSTR("set_led()\r\n"));
		set_output(LED1);
	}
}

int8_t led_get(struct packet_t *packet) {
	uart_putstr_P(PSTR("led_get()\r\n"));
	return set_data_int16(packet,get_output(LED1));
}

// configure the led pins 
void led_setup()
{
	drive(LED1);
	drive(LED2);
}

// disable the led pins, used for sleep
void led_disable()
{
	clr_output(LED1);
	clr_output(LED2);
	tristate(LED1);
	tristate(LED2);
}

// blink the power led
void led_blink1()
{
	set_output(LED1);
	delay_250ms();
	clr_output(LED1);
}


// blink the app led
void led_blink2()
{
	set_output(LED2);
	delay_250ms();
	clr_output(LED2);
}

