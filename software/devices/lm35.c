#include "board.h"
#include <stdint.h>
#include <avr/io.h>
#include "uart.h"

// Lecture d'un LM35 branché sur PC0

#define DEBUG

uint16_t adc_init() {
	ADCSRA |= (1 << ADEN) |  // Analog-Digital enable bit
	          (1 << ADPS1)|  // set prescaler to 8 (clock / 8)
                  (1 << ADPS0);  // set prescaler to 8 (doc Atmega168 23.8.2 p.258)
		     
	ADMUX = (1 << REFS0) | 	// Using AVcc as reference
		(2);		// Input is ADC2 (PC2)
}

uint16_t adc_read() {
	uint16_t result;

	ADCSRA |= (1 << ADEN);	// Enable ADC

	ADCSRA |= (1 << ADSC);	// Start conversion and discard it
	while (ADCSRA & (1 << ADSC));

	ADCSRA |= (1 << ADSC);	// Start conversion
	while (ADCSRA & (1 << ADSC));

	result = ADCL;	// Read low bits
	result = (ADCH << 8) + result;

	ADCSRA &= ~(1<<ADEN);

	return result;
}

void lm35_init() {
	adc_init();
}

int16_t lm35_read() {
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

	return temperature;
}
