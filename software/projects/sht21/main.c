#include "bugOne.h"
#include "rfm12.h"

#include <stdlib.h>

#include "avr_compat.h"

#include "apps.h"

#include "led.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "sht2x.h"
#include "ds18x20.h"

#include <avr/io.h>
#define DS18B20_GND  B,2

// XXX: Theses structures belong to PROGMEM ...
application_t applications[] = {
  {NULL,sht2x_temp_read,NULL,NULL},
  {NULL,sht2x_hum_read,NULL,NULL},
  {ds18x20_init,ds18x20_read,NULL,NULL},
  //{NULL,dht11_temperature_read,NULL,NULL},
  //{NULL,dht11_humidity_read,NULL,NULL},
  {NULL,NULL,NULL,NULL},
};


void io_init()
{
  drive(DS18B20_GND);
  clr_output(DS18B20_GND);
}

// The watchdog wake us, what we do ?
SIGNAL(WDT_vect) {
  bugone_wakeup();
}


int main(void) {
  int r = 0;
  char buf[16];
  uint8_t wake_up=10;

  eeprom_write_word(0,2);

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
#if 0
		delay_250ms();
		// Send sleeping message
		send(0xFF, SLEEP, get_tx_packet());
		led_blink2();
		rfm12_tick();
#endif
      wake_up=0;
    }
  bugone_sleep();
  }
}

