/* 
   bugOne battery value
   =====================
   Caution : the module enable the ADC, and never disable it.

	This module reads the battery voltage (followed on PC2 on the sensor shield)

	Please note that the device is not able to read more than twice Vcc (thanks to the voltage divider)

*/


#include "bugOne.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <stdint.h>
#include "avr_compat.h"
#include "adc.h"
#include "battery.h"



void battery_init(void *cfg) {
}


int8_t battery_get(struct packet_t *packet) {
	char buf[5];
	int32_t val,vcc;
	adc_init(3);
	delay_250ms();
	val = adc_read();
	adc_disable();
	delay_250ms();
	bandgap_init();
	delay_250ms();
	vcc = bandgap_read();
	bandgap_disable();
	itoa(vcc,buf,10);
	uart_putstr("VCC: ");
	uart_putstr(buf);
	vcc = 1100L * 1023 / vcc;
	itoa(vcc,buf,10);
	uart_putstr(" ( ->  ");
	uart_putstr(buf);
	uart_putstr(" mV )\r\n");
	itoa(val,buf,10);
	uart_putstr("Vbat: ");
	uart_putstr(buf);
	val = (vcc / 1023) * val * 2;
	itoa(val,buf,10);
	uart_putstr(" ( ->  ");
	uart_putstr(buf);
	uart_putstr(" mV )\r\n");
	return set_data_int16(packet,(int)val);
}

