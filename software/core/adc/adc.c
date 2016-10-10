#include "board.h"
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

#include "avr_compat.h"

#include "adc.h"

uint16_t adc_init(uint8_t pin) {
	ADCSRA |= (1 << ADEN) |  // Analog-Digital enable bit
	          (1 << ADPS1)|  // set prescaler to 8 (clock / 8)
                  (1 << ADPS0);  // set prescaler to 8 (doc Atmega168 23.8.2 p.258)
		     
	ADMUX = (1 << REFS0) | 	// Using AVcc as reference
		(pin);		// Input is ADC2 (PC2)
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

void adc_disable() {
  ADCSRA = 0;    // disable ADC
}


