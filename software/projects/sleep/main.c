#include "bugOne.h"
#include "avr_compat.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/power.h>



application_t applications[] = {};


// Note : 
// Additionnal infos for power registers is here : 
// http://www.nongnu.org/avr-libc/user-manual/group__avr__power.html


SIGNAL(WDT_vect) {
  static wd_count = 0;
  
  if (wd_count > 2)
  {
	power_all_enable();
	rfm12_wakeup();
	drive(LED1);
	drive(LED2);

	set_output(LED1);
	_delay_ms(500);
	clr_output(LED1);
	wd_count = 0;
  }
  else
	wd_count ++;
}




void system_sleep() {
  rfm12_sleep();
  tristate(LED1);
  tristate(LED2);
  power_all_disable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();

  PRR = 0xFF;
  sleep_mode();                        // System sleeps here
  sleep_disable();                     // System continues execution here when watchdog timed out 
}



int main ( void )
{
  char buf[20];
 
  bugone_init(applications);
  bugone_setup_watchdog(9);

  while (1) {
    _delay_ms(200); // wait for last char before sleep
    system_sleep();
  }
}
