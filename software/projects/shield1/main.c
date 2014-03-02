#include "bugOne.h"

#include <stdlib.h>
#include <avr/interrupt.h>

#include "avr_compat.h"
#include "config.h"

#include "apps.h"

#include "const.h"
#include "bandgap.h"
#include "led.h"
#include "photoresistor.h"
#include "dht11.h"

// Send datas every period seconds
const uint8_t period = 10;

// XXX: Theses structures belong to PROGMEM ...
const photoresistor_cfg_s photoresistor_cfg = {3};

application_t applications[] = {
 {NULL,const_read,NULL,NULL},
 {bandgap_init,bandgap_get,NULL,NULL},
 {photoresistor_init,photoresistor_read,NULL,(void*)&photoresistor_cfg},
 {NULL,dht11_temperature_read,NULL,NULL},
 {NULL,dht11_humidity_read,NULL,NULL},
 {NULL,NULL,NULL,NULL},
};

SIGNAL(WDT_vect) {
    // tell the AVR to power devices
    bugone_wakeup();
}

int main() {
    bugone_init(applications);

    bugone_setup_watchdog(8);

    uint8_t wake_up=2;
    while (1) {
        wake_up++;
        if (wake_up > 2) {
            led_blink2();
            bugone_send();
            wake_up=0;
        }
        bugone_sleep();
    }
}

