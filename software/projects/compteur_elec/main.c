#include "bugOne.h"
#include "rfm12.h"

#include <stdlib.h>

#include "avr_compat.h"

#include "apps.h"

#include "led.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "led.h"
#include "sht2x.h"
#include "teleinfo.h"

#include <avr/io.h>

// XXX: Theses structures belong to PROGMEM ...
application_t applications[] = {
  {NULL,sht2x_temp_read,NULL,NULL},
  {NULL,sht2x_hum_read,NULL,NULL},
  {teleinfo_init,teleinfo_get_ind_hchc,NULL,NULL},
  {teleinfo_init,teleinfo_get_ind_hchp,NULL,NULL},
  {teleinfo_init,teleinfo_get_iinst,NULL,NULL},
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
	 struct packet_t *packet;
	 int8_t len = 0;

    bugone_init(applications);
    bugone_setup_watchdog(9);

    while (1) 
    {
        wake_up++;
        if (wake_up > 1)
        {
            bugone_complete_wakeup();
				// We can't use bugone send, packets will be too long with teleinfo
				// We do everything manually !
				// First, let's get temp and humidity values
				packet = get_tx_packet();
				set_devices(packet,1,0x29);
				len = sht2x_temp_read(packet);
				set_devices(packet,2,0x29);
				len = sht2x_hum_read(packet);
				// Now let's read HCHC
				set_devices(packet,3,0x29);
				len = teleinfo_get_ind_hchc(packet);
				// No more space in packet, we send
				send(0xFF,6,packet);
            led_blink2();
				while(ctrl.txstate != STATUS_FREE) {
					rfm12_tick();
				}
				packet = get_tx_packet();
				set_devices(packet,4,0x29);
				len = teleinfo_get_ind_hchp(packet);
				set_devices(packet,5,0x29);
				len = teleinfo_get_iinst(packet);
				send(0xFF,6,packet);
            led_blink2();
				while(ctrl.txstate != STATUS_FREE) {
					rfm12_tick();
				}
            wake_up=0;
            bugone_complete_sleep();
        } else {
            delay_250ms();
        }
        bugone_sleep();
    }
}

