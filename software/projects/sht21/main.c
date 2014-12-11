#include "bugOne.h"
#include "rfm12.h"

#include <stdlib.h>

#include "avr_compat.h"

#include "apps.h"

#include "led.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "bandgap.h"
#include "led.h"
#include "sht2x.h"

#include <avr/io.h>
#define RFM12_CT B,7

// XXX: Theses structures belong to PROGMEM ...
application_t applications[] = {
  {NULL,sht2x_temp_read,NULL,NULL},
  {NULL,sht2x_hum_read,NULL,NULL},
  {bandgap_init,bandgap_get,NULL,NULL},
  {NULL,NULL,NULL,NULL},
};


// The watchdog wake us, what we do ?
SIGNAL(WDT_vect) {
    bugone_wakeup();
}


int main(void) {
    int r = 0;
    char buf[16];
    uint8_t wake_up=15;

    bugone_init(applications);
    bugone_setup_watchdog(9);

    while (1) 
    {
        wake_up++;
        if (wake_up > 15)
        {
            bugone_complete_wakeup();
            led_blink2();
            delay_500ms();
            bugone_send();
            wake_up=0;
            bugone_complete_sleep();
        } else {
			  delay_250ms();
		  }
        bugone_sleep();
    }
}

