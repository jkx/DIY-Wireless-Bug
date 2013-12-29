#include "bugOne.h"
#include "avr_compat.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/power.h>


#include "led.h"

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
	led_setup();
	led_blink1();

	wd_count = 0;
  }
  else
	wd_count ++;
}




void system_sleep() {
  rfm12_sleep();
  led_disable();
  power_all_disable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // set sleep mode and enable
  sleep_enable();

  sleep_mode();                        // let's sleep and wake-up
  sleep_disable();                     
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
