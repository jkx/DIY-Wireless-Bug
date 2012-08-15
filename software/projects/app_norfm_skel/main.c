
/* 

This is a really minimal skel : no wireless, just LEDs en UART.


*/


#include "bugOne.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>


#include "avr_compat.h"
#include "uart.h"
#include "config.h"

#include <stdio.h>

int main ( void )
{
  unsigned char i=0;
  char buf[16];

  drive(LED1);
  drive(LED2);

  set_output(LED1);
  set_output(LED2);
	
  uart_init();
  sei();

  uart_putstr_P(PSTR("AVR init complete\r\n"));

  while (1) {
    _delay_ms(200);
    sprintf(buf,"Foo : %d\r\n",i);
    uart_putstr(buf);
    toggle_output(LED2);
    i++;
  }
}
