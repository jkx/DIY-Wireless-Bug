
/* 

This is an minimal example howto use the watchdog, to put the bugOne 
in deep sleep mode. 

NOTE : In this state, the RFM12 still drain a lot of current. This 

*/


#include "bugOne.h"

#include <avr/interrupt.h>
#include <avr/power.h>

#include "uart.h"
#include "config.h"



application_t applications[] ={} ; 


void my_sleep() {
  led_disable();
  bugone_deep_sleep();
}


// The watchdog wake us, what we do ? 
SIGNAL(WDT_vect) {
  // tell the AVR to power devices
  power_all_enable(); 
  // just blink
  led_setup();
  led_blink1();
}



int main ( void )
{
    // cut & paste from the bugone_init() .. 
    // note that timer1.init() cause the power_all_enable() to bug .. 
    // and system randomly do some weird stuff .. 
    
    led_init();
	uart_init();
	rfm12_init();
	config_init();

	uart_putstr_P(PSTR("Firmware version "));
	uart_putstr_P(PSTR(FWVERSION_STR));
	uart_putstr_P(PSTR("\r\n"));

	//timer1_init();
	sei();
	uart_putstr_P(PSTR("bugOne init complete\r\n"));

    bugone_setup_watchdog(7);
  while (1) {
    delay_250ms(); // wait until uart flush..
    my_sleep();
    uart_putstr_P(PSTR("I'm back\r\n"));    
    
  }
}
