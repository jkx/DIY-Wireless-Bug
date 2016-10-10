#include "board.h"
#include <stdint.h>
#include <avr/io.h>
#include "adc.h"
#include "uart.h"
#include "lm35.h"

// Lecture d'un LM35 branché sur PC0

#define DEBUG

void lm35_init(void *lm35_cfg) {
	adc_init(((lm35_cfg_s*)lm35_cfg)->adc_pin);
}

int8_t lm35_read(struct packet_t *packet) {
	uint16_t voltage;
	uint16_t temperature;
	float tmp;
#ifdef DEBUG
	char buf[16];
#endif

	voltage = adc_read();

	tmp = voltage * 3.3 / 1024;
	temperature = tmp * 1000;

#ifdef DEBUG
	itoa(voltage,buf,10);
	uart_putstr_P(PSTR("Voltage (V): "));
	uart_putstr(buf);
	uart_putstr_P(PSTR("\r\n"));
	itoa(temperature,buf,10);
	uart_putstr_P(PSTR("Temperature (°C): "));
	uart_putstr(buf);
	uart_putstr_P(PSTR("\r\n"));
#endif

	return set_data_int16(packet, temperature);
}
