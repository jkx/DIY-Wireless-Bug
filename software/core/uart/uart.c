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

	toggle_output(LED1);

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

	drive(LED1);
	toggle_output(LED1);
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

void uart_hexdump(char *buf, int len)
{
	unsigned char x=0;
	char sbuf[3];

	while(len--){
		itoa(*buf++, sbuf, 16);
		if (sbuf[1] == 0) uart_putc(' ');
		uart_putstr(sbuf);
		uart_putc(' ');
		if(++x == 16) {
			uart_putstr_P(PSTR("\r\n"));
			x = 0;
		}
	}
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
