
/* 

This is a really minimal skel with RFM12: just send back .


*/


#include "bugOne.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>


#include "avr_compat.h"
#include "config.h"
#include "rfm12.h"
#include "board.h"

int main(void) {
	drive(LED1);
	set_output(LED1);
	rfm12_init();
	sei();

	uint8_t tx_buff[RFM12_RX_BUFFER_SIZE];

	while (1) {
		uint8_t size = 0;
		if (rfm12_rx_status() == STATUS_COMPLETE) {
			toggle_output(LED1);
			size = rfm12_rx_len();
			uint8_t *buff = rfm12_rx_buffer();
			uint8_t *pt = buff + size;
			uint8_t *pt2 = tx_buff;
			while (pt >= buff) {
				*pt2++ = *--pt;
			}
			rfm12_rx_clear();
		}
		rfm12_tick();
		if (size) {
			rfm12_tx(size, 1, tx_buff);
		}
	}
}
