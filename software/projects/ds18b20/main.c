#include "bugOne.h"

#include <stdlib.h>

#include "avr_compat.h"

#include "apps.h"

#include "led.h"
#include "ds18x20.h"
#include "dht11.h"
#include "bandgap.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>



#include <avr/io.h>
#define DS18B20_GND  D,6
#define DHT11_VCC    B,1


// XXX: Theses structures belong to PROGMEM ...
application_t applications[] = {
  {bandgap_init,bandgap_get,NULL,NULL},
  {ds18x20_init,ds18x20_read,NULL,NULL},
  //{NULL,dht11_temperature_read,NULL,NULL},
  //{NULL,dht11_humidity_read,NULL,NULL},
  {NULL,NULL,NULL,NULL},
};


void io_init()
{
  drive(DS18B20_GND);
  clr_output(DS18B20_GND);

  drive(DHT11_VCC);
  set_output(DHT11_VCC);
}


void io_clear()
{
  clr_output(DHT11_VCC);
}



// The watchdog wake us, what we do ?
SIGNAL(WDT_vect) {
  bugone_wakeup();
}


int main(void) {
  int r = 0;
  char buf[16];
  uint8_t wake_up=10;


  bugone_init(applications);
  bugone_setup_watchdog(9);
  
  while (1) 
  {
    wake_up++;
    if (wake_up > 10)
    {
      led_blink2();
      io_init();
      delay_500ms();
      bugone_send();
      wake_up=0;
    }
  io_clear();
  bugone_sleep();
  }
}

