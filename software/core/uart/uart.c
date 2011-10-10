/* USART-Init beim ATmegaXX */

#include "board.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>

#include "avr_compat.h"

#include "uart.h"

#define UART_RXBUFSIZE 50
#define UART_TXBUFSIZE 50


#define UART_BAUD_CALC(UART_BAUD_RATE,F_OSC) ((F_OSC)/((UART_BAUD_RATE)*16L)-1)

volatile static char rxbuf[UART_RXBUFSIZE];
volatile static char *volatile rxhead, *volatile rxtail;


SIGNAL(USART_RX_vect) {
	int diff; 

	/* buffer full? */
	diff = rxhead - rxtail;
	if ( diff < 0 ) diff += UART_RXBUFSIZE;
	if (diff < UART_RXBUFSIZE -1) {
		// buffer NOT full
		*rxhead = UDR0;
		if (++rxhead == (rxbuf + UART_RXBUFSIZE)) rxhead = rxbuf;
	} else {
		UDR0;				//reads the buffer to clear the interrupt condition
	}
}


void uart_init() {
	UBRR0H=(uint8_t)(UART_BAUD_CALC(UART_BAUD_RATE,F_CPU)>>8);
	UBRR0L=(uint8_t)(UART_BAUD_CALC(UART_BAUD_RATE,F_CPU));

	UCSR0B = ((1<<TXEN0) | (1 << RXEN0) | (1 << RXCIE0 ));		//UART TX einschalten
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); 	//Asynchron 8N1
	UCSR0A = (1 << RXC0);

	// init buffers
	rxhead = rxtail = rxbuf;
}

void uart_putc(char c) {
	while (!(UCSR0A & (1<<UDRE0))); /* warten bis Senden moeglich                   */
	UDR0 = c;                      /* schreibt das Zeichen x auf die Schnittstelle */
}


void uart_putstr(char *str) {
	while(*str) {
		uart_putc(*str++);
	}
}

void uart_putstr_P(PGM_P str) {
	char tmp;
	while((tmp = pgm_read_byte(str))) {
		uart_putc(tmp);
		str++;
	}
}

void uart_hexdump_hex(uint8_t *buf, int len) {
	const char hex[] = "0123456789ABCDEF";
	char sbuf[4] = "XX ";

	while (len--) {
		sbuf[0] = hex[*buf / 16];
		sbuf[1] = hex[*buf % 16];
		buf++;
		uart_putstr(sbuf);
	}
}

void uart_hexdump_ascii(uint8_t *buf, int len) {
	char sbuf[3];

	while (len--) {
		if ((*buf >= 32) && (*buf <= 128)) {
			uart_putc(*buf);
		} else {
			uart_putc('.');
		}
		buf++;
	}
}

/* Produce a nice hexdump output */
void uart_hexdump(uint8_t *buf, int len)
{
	uint8_t i;

	while (len > 16) {
		uart_hexdump_hex(buf,16);
		uart_putstr_P(PSTR("  "));
		uart_hexdump_ascii(buf,16);
		uart_putstr_P(PSTR("\r\n"));
		len-=16;
		buf+=16;
	}
	uart_hexdump_hex(buf,len);
	for (i = 0; i < 16 - len; i++) {
		uart_putstr_P(PSTR("   "));
	}
	uart_putstr_P(PSTR("  "));
	uart_hexdump_ascii(buf,len);
	uart_putstr_P(PSTR("\r\n"));
}


char uart_getc()
{
	char val;

	while(rxhead==rxtail) ;

	val = *rxtail;
 	if (++rxtail == (rxbuf + UART_RXBUFSIZE)) rxtail = rxbuf;

	return val;
}

// returns 1 on success
char uart_getc_nb(char *c)
{
	if (rxhead==rxtail) return 0;

	*c = *rxtail;
 	if (++rxtail == (rxbuf + UART_RXBUFSIZE)) rxtail = rxbuf;

	return 1;
}
