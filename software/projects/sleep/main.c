#include "bugOne.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <avr/sleep.h>
#include <stdlib.h>

#include "avr_compat.h"
#include "rfm12.h"
#include "uart.h"
#include "config.h"

#include "ping.h"


#include <avr/wdt.h>


SIGNAL(WDT_vect) {
  drive(LED1);
  drive(LED2);

  set_output(LED1);
  _delay_ms(500);
  clr_output(LED1);
}


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


void system_sleep() {
  tristate(LED1);
  tristate(LED2);
  cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();

  PRR = 0xFF;
  sleep_mode();                        // System sleeps here
  sleep_disable();                     // System continues execution here when watchdog timed out 
  sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON
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

  /*
  uart_putstr_P(PSTR("Firmware version "));
  uart_putstr_P(PSTR(FWVERSION));
  uart_putstr_P(PSTR("\r\n"));
  */

  config_init();

  /*
  uart_putstr_P(PSTR("Node address : "));
  itoa(config.address,buf,10);
  uart_putstr(buf);
  uart_putstr_P(PSTR("\r\n"));
  */

  _delay_ms(250);
  rfm12_init();
  _delay_ms(250);


  _delay_ms(1000);
  clr_output(LED2);
 

  #include <rfm12/include/rfm12_core.h>
  #include <rfm12/include/rfm12_hw.h>

  // put the RFM is sleep mode
  //rfm12_data(RFM12_CMD_PWRMGT | RFM12_PWRMGT_DC);
  rfm12_data(0x8205);


  sei();
  while (1) {
    _delay_ms(200); // wait for last char before sleep
    system_sleep();
  }
}
