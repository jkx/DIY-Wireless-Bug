#include "bugOne.h"

#include <stdlib.h>

#include "avr_compat.h"
#include "rfm12.h"
#include "config.h"

#include "apps.h"
#include "hh10d.h"
#include "led.h"
#include "const.h"
//#include "button.h"

// XXX: Theses structures belong to PROGMEM ...

application_t applications[] = {
 {NULL,const_read,NULL,NULL},
 {NULL,led_get,led_set,NULL},
 //{button_init,button_read,NULL,NULL},
 {hh10d_init,hh10d_read,NULL,NULL},
 {NULL,NULL,NULL,NULL},
};
