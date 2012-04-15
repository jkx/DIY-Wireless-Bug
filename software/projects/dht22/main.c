#include "bugOne.h"

#include <stdlib.h>

#include "avr_compat.h"
#include "config.h"

#include "apps.h"

#include "const.h"
#include "led.h"
#include "dht22.h"

// XXX: Theses structures belong to PROGMEM ...

application_t applications[] = {
 {NULL,const_read,NULL,NULL},
 {NULL,dht22_temperature_read,NULL,NULL},
 {NULL,dht22_humidity_read,NULL,NULL},
 {NULL,NULL,NULL,NULL},
};
