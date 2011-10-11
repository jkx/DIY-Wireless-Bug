#include "board.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <avr/sleep.h>
#include <avr/power.h>

#include "aes.h"

#include "uart.h"
#include "avr_compat.h"

void memxor(uint8_t *a, uint8_t *b, uint8_t len) {
	while (len--) {
		*a = *b ^ *a;
		a++; b++;
	}
}

int main ( void )
{
  uint8_t *bufcontents;
  uint8_t i;
  uint8_t tv[] = "foobar1";
  uint16_t ticker = 0;
  uint8_t rc;
  aes128_ctx_t ctx;

  uint8_t key[] = "0123456789ABCDEF";
  uint8_t IV[] = "FEDCBA9876543210";
  uint8_t text[] = "Hello rfm12 world. I've gonna cipher you       ";
	
  drive(LED1);
  drive(LED2);

  toggle_output(LED1);
	
  uart_init();

  _delay_ms(250);
  _delay_ms(250);

  sei();

  toggle_output(LED2);
  uart_putstr ("AVR Boot Ok\r\n");
  _delay_ms(250);
  toggle_output(LED2);

  aes128_init(key,&ctx);

  while (1) {
    uart_putstr("key = ");
    uart_putstr(key);
    uart_putstr("\r\n");

    uart_putstr("text = ");
    uart_putstr(text);
    uart_putstr("\r\n");

    /* Ciphering in CBC mode */
    memxor(text,IV,16);
    aes128_enc(text,&ctx);
    memxor(text+16,text,16);
    aes128_enc(text+16,&ctx);
    memxor(text+32,text+16,16);
    aes128_enc(text+32,&ctx);

    uart_putstr("text ciphered = \r\n");
    uart_hexdump(text,sizeof(text));

    /* Deciphering in CBC mode */
    aes128_dec(text+32,&ctx);
    memxor(text+32,text+16,16);
    aes128_dec(text+16,&ctx);
    memxor(text+16,text,16);
    aes128_dec(text,&ctx);
    memxor(text,IV,16);

    uart_putstr("text unciphered = ");
    uart_putstr(text);
    uart_putstr("\r\n");

    /* Let change the IV */
    IV[0]++;

    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
  }
}
