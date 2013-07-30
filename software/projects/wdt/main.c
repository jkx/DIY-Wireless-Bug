
/* 

This is an example howto use the watchdog 


*/


#include "bugOne.h"


#include <avr/interrupt.h>
#include <avr/power.h>


#include "uart.h"
#include "config.h"

//#include <stdio.h>


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
  led_blink2();
}



int main ( void )
{
  char buf[16];

  led_setup();
  led_blink1();
  
  sei();  
  uart_init();

  uart_putstr_P(PSTR("AVR init complete\r\n"));

  bugone_setup_watchdog(7);
  while (1) {
    delay_250ms(); // wait until uart flush..
    my_sleep();
    uart_putstr_P(PSTR("I'm back\r\n"));    
    
  }
}
