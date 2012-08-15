/* 
   bugOne wireless test
   ====================
   - register the base bugOne functions : leds

 */ 


#include "bugOne.h"
#include <stdlib.h>
#include "config.h"

// include devices
#include "const.h"
#include "led.h"
#include "bandgap.h"


application_t applications[] = {
 {NULL,const_read,NULL,NULL},
 {NULL,led_get,led_set,NULL},
 {bandgap_init,bandgap_get,NULL,NULL},
 {NULL,NULL,NULL,NULL}
};

