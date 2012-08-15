/* 
   bugOne wireless test
   ====================
   - register the base bugOne functions : leds


 */ 


#include "bugOne.h"
#include <stdlib.h>
#include "config.h"

#include "led.h"
#include "const.h"


application_t applications[] = {
 {NULL,const_read,NULL,NULL},
 {NULL,led_get,led_set,NULL},
 {NULL,NULL,NULL,NULL}
};

