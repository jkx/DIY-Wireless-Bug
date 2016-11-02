/* 
   bugOne onboard led driver
   =========================
   LED1 is the power led, in normal operation it should be on,
   in power-down mode, it should only blink
   
   LED2 is the app led, feel free to use it
*/


#include "bugOne.h"
#include "switch.h"
#include "led.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "avr_compat.h"

// Init on board LEDs
void switch_init(void *cfg) {
	drive(RELAY_PIN);
	delay_500ms();
}

int8_t switch_set(struct packet_t *packet) {
//	uart_putstr_P(PSTR("switch_set()\r\n"));
//	uart_putc(get_data_type(packet));//!=0x49) { uart_putstr_P(PSTR("not an integer")); return; }
	get_data_type(packet);
	if (get_data_int16(packet) == 0) {
		uart_putstr_P(PSTR("clr_switch()\r\n"));
		set_output(RELAY_PIN);
	} else {
		uart_putstr_P(PSTR("set_switch()\r\n"));
		clr_output(RELAY_PIN);
	}
	return 1;
}

int8_t switch_get(struct packet_t *packet) {
	uart_putstr_P(PSTR("switch_get()\r\n"));
	int16_t state = (get_output(RELAY_PIN) == 0) ? 1 : 0;
	return set_data_int16(packet,state);
}
