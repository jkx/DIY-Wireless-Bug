#include "bugOne.h"
#include "avr_compat.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/power.h>


#include "led.h"

application_t applications[] = {};

//****************************************************************
// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
// for more infos check this
// http://interface.khm.de/index.php/lab/experiments/sleep_watchdog_battery/
void setup_watchdog(int val) {
  unsigned char  bb;
  if (val > 9 ) val=9;
  bb=val & 7;
  if (val > 7) bb|= (1<<5);
  bb|= (1<<WDCE);

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCSR = bb;
  WDTCSR |= _BV(WDIE);
}


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

  cbi( SMCR,SE );      // sleep enable, power down mode
  cbi( SMCR,SM0 );     // power down mode
  sbi( SMCR,SM1 );     // power down mode
  cbi( SMCR,SM2 );     // power down mode

  setup_watchdog(9);

  drive(LED2);
  set_output(LED2);

  uart_init();
  uart_putstr("Boot\r\n");

  //config_init();

  _delay_ms(250);
  rfm12_init();
  _delay_ms(250);


  _delay_ms(1000);
  clr_output(LED2);
 
  // put the RFM is sleep mode
  //rfm12_data(RFM12_CMD_PWRMGT | RFM12_PWRMGT_DC);
  rfm12_data(0x8205);

  
 
  //bugone_init(applications);
  //bugone_setup_watchdog(9);

  while (1) {
    _delay_ms(200); // wait for last char before sleep
    system_sleep();
  }
}
