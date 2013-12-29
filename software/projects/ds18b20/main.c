#include "bugOne.h"

#include <stdlib.h>

#include "avr_compat.h"
#include "config.h"

#include "apps.h"

#include "led.h"
#include "ds18x20.h"
#include "dht11.h"
#include <avr/pgmspace.h>
#include <avr/interrupt.h>



#include <avr/io.h>
#define DS18B20_GND  D,6
#define DHT11_VCC    B,1


// XXX: Theses structures belong to PROGMEM ...

application_t applications[] = {
  {ds18x20_init,ds18x20_read,NULL,NULL},
  {NULL,dht11_temperature_read,NULL,NULL},
  {NULL,dht11_humidity_read,NULL,NULL},
  {NULL,NULL,NULL,NULL},
};


void io_init()
{
  drive(DS18B20_GND);
  clr_output(DS18B20_GND);

  drive(DHT11_VCC);
  set_output(DHT11_VCC);
}


int main(void) {
  io_init();
  bugone_init(applications);

  int r = 0;
  char buf[16];
  
  while (1) {
    //bugone_loop();

    set_output(DHT11_VCC);
    r = dht11_read();
    sprintf(buf,"dht11_read=%d\r\n",r);
    uart_putstr(buf);

    r = dht11_humidity_val();
    sprintf(buf,"hum=%d  ",r);
    uart_putstr(buf);

    r = dht11_temperature_val();
    sprintf(buf,"tmp=%d\r\n",r);
    uart_putstr(buf);

    clr_output(DHT11_VCC);
    delay_1s();
    delay_1s();
    delay_1s();
    delay_1s();



  }
}

