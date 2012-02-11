#include "bugOne.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <avr/sleep.h>

#include "avr_compat.h"
#include "rfm12.h"
#include "uart.h"

void adc_init() {
	// Init ADC
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	// Init ADMUX to read from ADC2 (light sensor)
	ADMUX = _BV(REFS0) | 0x02;
}

/* Result is available in ADC as an uint16_t or ADC[H/L] as two uint8_t */
void adc_read(uint8_t adc, uint16_t *value) {
		ADMUX = _BV(REFS0) | adc;
		ADCSRA |= _BV(ADEN);

		ADCSRA |= _BV(ADSC);
		while(bit_is_set(ADCSRA, ADSC));

		*value = ADC;

		ADCSRA &= ~(_BV(ADEN));
}

int main(void) {
	uint8_t tx_buffer[4]; // Two uint16_t values

	adc_init();
	rfm12_init();

	sei();
	drive(LED1);
	drive(LED2);

	clr_output(LED1);
	clr_output(LED2);

	// Init PB2 to power sensors
	DDRB |= 0x04;

	uint8_t tick = 0;
	while (1) {
		// Power up the shield
		PORTB |= 0x04;

		// We don't care about any message received by now
		if (rfm12_rx_status() == STATUS_COMPLETE) {
			rfm12_rx_clear();
			rfm12_tick();
		}
		
		if (tick++ == 0) {
			set_output(LED1);

			// Read light sensor
			adc_read(0x02, (uint16_t *)&tx_buffer[0]);

			// Read temperature sensor
			adc_read(0x03, (uint16_t *)&tx_buffer[2]);

			rfm12_tx(4, 0 /*type*/, tx_buffer);
			clr_output(LED1);
		}

		// Power down the shield
		PORTB |= 0x04;

		rfm12_tick();

		// Wait
		_delay_ms(10);
	}

}
