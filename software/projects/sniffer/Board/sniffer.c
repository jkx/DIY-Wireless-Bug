#include "bugOne.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <avr/sleep.h>

#include "avr_compat.h"
#include "rfm12.h"
#include "uart.h"

#if RFM12_UART_DEBUG
#error "sniffer over serial isn't compatible with rfm12 debug over uart"
#endif

uint8_t size = 0, count = 0;

// We use timer 0 to timeout on uart operation
// We reset everything of overflow => timeout is set to 0.03s
void timer0_init() {
	// Set timer 0 prescaler
	TCCR0B |= ((1 << CS00) | (1 << CS02)); // Set up timer at Fcpu/1024
	// Enable Overflow Interrupt Enable
	TIMSK0|=(1<<TOIE0);
}

ISR(TIMER0_OVF_vect) {
	size = 0;
	count =0;
}

int main(void) {
	uint8_t *rx_buffer;
	uint8_t  tx_buffer[256]; // Not RFM12_TX_BUFFER_SIZE since we don't know what will be sent on uart
	uint8_t c;

	uart_init();
	rfm12_init();
	timer0_init();

	sei();
	drive(LED1);
	drive(LED2);

        set_output(LED1);
        _delay_ms(250);
        set_output(LED2);
        _delay_ms(250);
        _delay_ms(250);
	clr_output(LED2);
        _delay_ms(250);
	clr_output(LED1);

	while (1) {
		if (rfm12_rx_status() == STATUS_COMPLETE) {
			rx_buffer = rfm12_rx_buffer();
			uint8_t length = rfm12_rx_len();
			uint8_t checksum = 0x00;
			uart_putc(length);
			while (length--) {
				TCNT0 = 0;
				uint8_t data = *rx_buffer++;
				uart_putc(data);
				checksum ^= data;
			}
			toggle_output(LED2);
			uart_putc(checksum);
			rfm12_rx_clear();
		}

		if (size != 0 && size == count) {
			if (rfm12_tx(size, 0 /*type*/, tx_buffer) == RFM12_TX_ENQUEUED) {
				toggle_output(LED1);
				size = count = 0;
			}
		}

		if (uart_getc_nb(&c) > 0) {
			TCNT0 = 0;
			if (size == 0) {
				size = c;
				count = 0;
			} else {
				tx_buffer[count] = c;
				count++;
			}
		}

		rfm12_tick();
	}

}
