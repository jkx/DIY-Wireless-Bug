
#include "bugOne.h"

#include <stdlib.h>

#include "avr_compat.h"

#include "apps.h"

#include "led.h"
#include "bandgap.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>



#include <avr/io.h>


extern uint8_t send_flush;

// XXX: Theses structures belong to PROGMEM ...
application_t applications[] = {
  {bandgap_init,bandgap_get,NULL,NULL},
  {NULL,NULL,NULL,NULL},
};



// The watchdog wake us, what we do ?
SIGNAL(WDT_vect) {
  bugone_wakeup();
}


#define BUTTON1 D,4
void button_init(void* cfg) {
	// Button is connected to PD4 / PCINT20
	PCMSK2 |= (1 << PCINT20);
	PCICR |= (1 << PCIE2);
}

ISR (PCINT2_vect) {
	uart_putstr_P(PSTR("ISR\r\n"));
	send_flush = 0;
}

int8_t button_read(struct packet_t *packet) {
	uart_putstr_P(PSTR("button read\r\n"));
	set_data_int16(packet,get_input(BUTTON1));
	return 3;
}



int main(void) {
  int r = 0;
  char buf[16];
  uint8_t wake_up=10;


  bugone_init(applications);
  //bugone_setup_watchdog(9);
  button_init(NULL);

  while (1) 
  {
    wake_up++;
    if (wake_up > 10)
    {
      led_blink2();
      delay_500ms();
      bugone_send();
      wake_up=0;
    }
	//bugone_sleep();
  }
}

