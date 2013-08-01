
/* 

This is an minimal example howto use the watchdog, to put the bugOne 
in deep sleep mode. 

NOTE : In this state, the bugOne drains around 20uA, and can only send

*/


#include "bugOne.h"

#include <avr/interrupt.h>
#include <avr/power.h>

#include "uart.h"
#include "config.h"


#define RFM12_USE_POWER_CONTROL 1


application_t applications[] ={} ; 


void my_sleep() {
    delay_250ms();
    rfm12_power_down();
    led_disable();
    bugone_deep_sleep();
}


// The watchdog wake us, what we do ? 
SIGNAL(WDT_vect) {
    // tell the AVR to power devices
    power_all_enable(); 
    rfm12_power_up();
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
	rfm12_init();
	config_init();

	//timer1_init();
	sei();
    bugone_setup_watchdog(9);

    while (1) {
        my_sleep();
    }
}
