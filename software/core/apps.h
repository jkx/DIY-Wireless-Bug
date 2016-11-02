#ifndef APPS_H
#define APPS_H

#include <stdint.h>
#include "network.h"

enum {
	TEMPERATURE_APP, // Temperature measurement (SHT21, DS18x20, LM35)
	HUMIDITY_APP, // DHTX1, SHTX1
	BATTERY_APP, // battery measurement (ADC)
	BANDGAP_APP, // Bandgap measurement
	EVENT_APP, // Apps which send an event (button pressed, threshold reached, ...)
	SWITCH_APP, // Switch apps, supports turning on or off a switch (relay, ...)
	LUM_APP, // Luminosity measurement
 	DIMMER_APP, // Dimmmer (DAC, LEDs, ...)
};



typedef struct {
	void (*init)(void*);
	int8_t (*get)(struct packet_t*);
	int8_t (*set)(struct packet_t*);// Return true if require update
	void *cfg;
	// Type of data from previous enum
	uint8_t type;
	// Number of wdt interrupt before transmission
	int sleeptime;
	// Number of interrupt since last transmission
	int current_time;
} application_t;


void apps_set(application_t* apps, uint8_t size);
application_t* app_get(uint8_t sensor);
void apps_setup(application_t* apps);
void apps_init();


#endif
