#include "board.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <avr/sleep.h>
#include <avr/power.h>


#include "rfm12_config.h"
#include "rfm12.h"
#include "uart.h"
#include "avr_compat.h"

int main ( void )
{
  uint8_t *bufcontents;
  uint8_t i;
  uint8_t tv[] = "foobar1";
  uint16_t ticker = 0;
  uint8_t rc;
	
  drive(LED1);
  drive(LED2);

  toggle_output(LED1);
	
  uart_init();

  //_delay_ms(250);
  //_delay_ms(250);
  _delay_ms(250);
  rfm12_init();
  _delay_ms(250);
  //rfm12_set_wakeup_timer(100);	

  sei();

  toggle_output(LED2);
  uart_putstr ("AVR Boot Ok\r\n");
  _delay_ms(250);
  toggle_output(LED2);


  while (1)
    {
      ticker++;
      if (rfm12_rx_status() == STATUS_COMPLETE)
	{
	  uart_putstr ("new packet:[");
	  bufcontents = rfm12_rx_buffer();

	  // dump buffer contents to uart			
	  for (i=0;i<rfm12_rx_len();i++)
	    {
	      uart_putc ( bufcontents[i] );
	    }
	  uart_putstr ("]\r\n");
	  rfm12_rx_clear();
	}

      
      rfm12_tick();
      // send data
      if (ticker > 50000) 
	{ 
	  ticker = 0;
	  rc = rfm12_tx (sizeof(tv), 0, tv);
	  if (rc != RFM12_TX_ENQUEUED) {
	  	toggle_output(LED2);
	  }
          toggle_output(LED1);
          uart_putc('.');
	}
    }


}
