#include "board.h"
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "hh10d.h"

// Lecture d'un HH10D branché sur PD3

#define DEBUG
int cnt;
int old_cnt;
int sens;
int offset;

ISR(INT1_vect)
{
  cnt ++;
}

void hh10d_freq() {
	old_cnt = cnt;
	cnt = 0;
}

void hh10d_init(void *cfg) {
	// Read calibrate paremeter with TWI
	int rc;
	char buf[6];
	twi_init();
	rc = ee24xx_read_bytes(10,4,buf);
	if (rc != 4) {
		sens = 0; offset = 0;
		return;
	}
#ifdef DEBUG
	uart_hexdump(buf,4);
	uart_putc ('\r');      
	uart_putc ('\n');      
#endif
	sens = buf[0] * 256 + buf[1];
	offset = buf[2] * 256 + buf[3];
#ifdef DEBUG
    itoa(sens,buf,10);
    uart_putstr(buf);
    uart_putstr_P(PSTR("\r\n"));
    itoa(offset,buf,10);
    uart_putstr(buf);
    uart_putstr_P(PSTR("\r\n"));
#endif

	// rising edge
	EICRA |= (1 << ISC10) | (1 << ISC11);
	// enable INT1
	EIMSK |= (1 << INT1);
}

int8_t hh10d_read(struct data_t *data) {
    int RH;
    char buf[6];

    uart_putstr_P(PSTR("hh10d read\r\n"));
    RH = (offset - (double)old_cnt) * sens / 4096.0;

#ifdef DEBUG
    itoa(old_cnt,buf,10);
    uart_putstr(buf);
    uart_putstr_P(PSTR("\r\n"));

    itoa(RH,buf,10);
    uart_putstr(buf);
    uart_putstr_P(PSTR("\r\n"));
#endif

    if (data->remaining_len < 2) return -1;
    return set_data_int16(data,RH);
}
