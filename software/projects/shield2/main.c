#include "bugOne.h"

#include <stdlib.h>

#include "avr_compat.h"
#include "config.h"

#include "apps.h"

#include "const.h"
#include "bandgap.h"
#include "led.h"
#include "ds18x20.h"

// Send datas every period seconds
const uint8_t period = 5;

// XXX: Theses structures belong to PROGMEM ...
application_t applications[] = {
 {NULL,const_read,NULL,NULL},
 {bandgap_init,bandgap_get,NULL,NULL},
 {ds18x20_init,ds18x20_read,NULL,ds18x20_sleep,ds18x20_wakeup,NULL},
 {NULL,NULL,NULL,NULL},
};
