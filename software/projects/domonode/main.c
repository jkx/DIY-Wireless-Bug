#include "bugOne.h"
#include "rfm12.h"

#include <stdlib.h>

#include "avr_compat.h"

#include "apps.h"

#include "led.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "nodeconfig.h"
#include "battery.h"
#include "random.h"
#include "bandgap.h"
#include "led.h"
#include "sht2x.h"

#include <avr/io.h>
#include <avr/power.h>
#define RFM12_CT B,7



// XXX: Theses structures belong to PROGMEM ...
application_t applications[] = {
	{NULL,sht2x_temp_read,NULL,NULL,TEMPERATURE_APP,1,1},
	{NULL,sht2x_hum_read,NULL,NULL,HUMIDITY_APP,1,1},
	{battery_init,battery_get,NULL,NULL,BATTERY_APP,60,60}, // 60 * 8mn = 8h
	//{bandgap_init,bandgap_get,NULL,NULL,BANDGAP_APP,1},
	{NULL,NULL,NULL,NULL},
};



// The watchdog wake us, what we do ?
SIGNAL(WDT_vect) {
	bugone_wakeup();
}


int main(void) {
	int r = 0;
	char buf[16];
	uint8_t wake_up=60;
	uint8_t *bufcontents;

	bugone_init(applications);
	bugone_set_config_period(30);
	bugone_setup_watchdog(9);

	while (1) 
	{
		wake_up++;
		if (wake_up > 60) // 8mn
		{
			bugone_complete_wakeup();
			led_blink2();
			delay_500ms();
			bugone_send_receive();
			//bugone_send();
			//delay_500ms();
			//// Receive packets
			//while (rfm12_rx_status() == STATUS_COMPLETE) {
			//	bufcontents=rfm12_rx_buffer();
			//	recv(bufcontents);
			//	led_blink2();
			//	delay_250ms();
			//}
			wake_up=0;
			bugone_complete_sleep();
		} else {
			delay_250ms();
		}
		bugone_sleep();
	}
}

