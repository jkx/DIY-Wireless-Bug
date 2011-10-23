#include "board.h"
#include <string.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "config.h"
#include "rfm12_config.h"
#include "rfm12.h"
#include "uart.h"
#include "avr_compat.h"

/* Ping command. To ping destination address 25 :
   P25 
 */
void run_cmd_ping(char *params) {
	uint8_t dst;
	
	dst=atoi(params);

	send_ping(dst);
}

void run_cmd(char *cmd) {
	switch (cmd[0]) {
		case 'P':
		case 'p':
			cmd+=1;
			run_cmd_ping(cmd);
			break;
	}
}

int main ( void )
{
  uint8_t *bufcontents;
  uint16_t ticker = 0;
  uint16_t packet_count = 0;
  uint8_t len;
  char strbuf[6];
  char cmd[10];
  char *c;
	
  drive(LED1);
  drive(LED2);

  toggle_output(LED1);
  toggle_output(LED2);
	
  uart_init();

  uart_putstr_P(PSTR("Firmware version "));
  uart_putstr_P(PSTR(FWVERSION));
  uart_putstr_P(PSTR("\r\n"));

  config_init();

  uart_putstr_P(PSTR("Node address : "));
  itoa(config.address,strbuf,10);
  uart_putstr(strbuf);
  uart_putstr_P(PSTR("\r\n"));

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

      if (ticker > 50000) {
          ticker = 0;
          toggle_output(LED2);
      }

	  if (uart_getc_nb(c) == 1) {
	    if (*c == 13) {
		  *c = 0;
		  run_cmd(cmd);
		  c = cmd;
		} else if ((c - cmd) < sizeof(cmd)) {
	  	  c++; // ahah
		}
	  }

      rfm12_tick();
  }
}
