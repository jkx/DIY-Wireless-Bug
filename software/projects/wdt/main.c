
/*

This is an minimal example howto use the watchdog, to put the bugOne
in deep sleep mode.

NOTE : In this state, the bugOne drains around 120uA, and can only send

*/



#include "bugOne.h"

#include <avr/interrupt.h>
#include <stdlib.h>


// devices
#include "bandgap.h"
#include "avr_compat.h"


#define RFM12_USE_POWER_CONTROL 1


application_t applications[] = { 
    {bandgap_init,bandgap_get,NULL,NULL},
    {NULL,NULL,NULL,NULL},
};


void sleep() {
  bugone_sleep();
}


// The watchdog wake us, what we do ?
SIGNAL(WDT_vect) {
  bugone_wakeup();
}


int main ( void )
{
  bugone_init(applications);
  bugone_setup_watchdog(8);

  uint8_t wake_up=2;
  while (1) 
  {
	wake_up++;
	if (wake_up > 2)
	{
	  led_blink2();
	  bugone_send();
	  wake_up=0;
	}
	sleep();
  }
}


