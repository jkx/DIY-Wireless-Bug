#include "board.h"
#include <string.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "rfm12_config.h"
#include "rfm12.h"
#include "uart.h"
#include "avr_compat.h"

int main ( void )
{
  uint8_t *bufcontents;
  uint16_t ticker = 0;
  uint16_t packet_count = 0;
  uint8_t len;
  char strbuf[6];
	
  drive(LED1);
  drive(LED2);

  toggle_output(LED1);
  toggle_output(LED2);
	
  uart_init();

  _delay_ms(250);
  _delay_ms(250);
  _delay_ms(250);
  rfm12_init();
  _delay_ms(250);

  sei();

  toggle_output(LED2);
  uart_putstr ("AVR Boot Ok\r\n");
  uart_putstr ("RFM12 traffic sniffer\r\n");
  uart_putstr ("=======================\r\n");
  _delay_ms(250);
  toggle_output(LED1);


  while (1) {
      ticker++;
      if (rfm12_rx_status() == STATUS_COMPLETE)
	{
          toggle_output(LED1);
          packet_count++;
	  bufcontents = rfm12_rx_buffer();
          len = rfm12_rx_len();
          uart_putstr ("Packet ");
          itoa(packet_count,strbuf,10);
	  uart_putstr (strbuf);
          uart_putstr (" length ");
          itoa(len,strbuf,10);
	  uart_putstr (strbuf);
          uart_putstr ("\r\n");
          uart_hexdump((char*)bufcontents,len);
	  rfm12_rx_clear();
	}
      _delay_ms(5);

      if (ticker > 50000) {
          ticker = 0;
          toggle_output(LED2);
      }
      
      rfm12_tick();
  }
}
