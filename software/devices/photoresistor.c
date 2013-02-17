#include "board.h"
#include <stdint.h>
#include <avr/io.h>
#include "uart.h"
#include "photoresistor.h"
#include "value.h"

// Lecture d'une photoresistance branché sur l'ADC

uint16_t adc_init(uint8_t pin) {
	ADCSRA |= (1 << ADEN) |  // Analog-Digital enable bit
	          (1 << ADPS1)|  // set prescaler to 8 (clock / 8)
                  (1 << ADPS0);  // set prescaler to 8 (doc Atmega168 23.8.2 p.258)
		     
	ADMUX = (1 << REFS0) | 	// Using AVcc as reference
		(pin);		// Input is ADC2 (PC2)
}

uint16_t adc_read() {
	uint16_t result;

        adc_init(3);

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

void photoresistor_init(void *photoresistor_cfg) {
	adc_init(((photoresistor_cfg_s*)photoresistor_cfg)->adc_pin);
}

int8_t photoresistor_read(struct packet_t *packet) {
	uint16_t value;
	value = adc_read();
	return set_data_int16(packet, value);
}
