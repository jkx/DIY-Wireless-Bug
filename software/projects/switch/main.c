#include "bugOne.h"
#include "rfm12.h"

#include <stdlib.h>

#include "avr_compat.h"

#include "apps.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "led.h"
#include "switch.h"
#include "random.h"

#include <avr/io.h>
#include <avr/power.h>
#define RFM12_CT B,7
#ifdef BUGONE_ANNOUNCE_SLEEP
#undef BUGONE_ANNOUNCE_SLEEP
#endif
#define BUGONE_ANNOUNCE_SLEEP 0

// XXX: Theses structures belong to PROGMEM ...
application_t applications[] = {
  {switch_init,switch_get,switch_set,NULL,SWITCH_APP,1,1},
  {NULL,NULL,NULL,NULL}
};


// The watchdog wake us, what we do ?
volatile uint8_t wake_up;

SIGNAL(WDT_vect) {
	 wake_up++;
}


int main(void) {
    int r = 0;
    char buf[16];
	 wake_up = 20;

    bugone_init(applications);
	 bugone_set_config_period(30);
    bugone_setup_watchdog(9);
	 bugone_complete_wakeup();


	 while (1) 
	 {
		 bugone_receive();
		 if (wake_up > 6)
		 {
			 led_blink2();
			 bugone_send_receive();
			 wake_up=0;
		 } else {
			 delay_250ms();
		 }
	 }
}

