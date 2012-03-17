#include "bugOne.h"
#include <stdlib.h>
#include "config.h"

#include "led.h"
#include "const.h"
#include "lm35.h"

// XXX: Theses structures belong to PROGMEM ...
const lm35_cfg_s lm35_cfg = {3};

application_t applications[] = {
 {NULL,const_read,NULL,NULL},
 {NULL,led_get,led_set,NULL},
 //{button_init,button_read,NULL,NULL},
 {lm35_init,lm35_read,NULL,(void*)&lm35_cfg},
 {NULL,NULL,NULL,NULL}
};

