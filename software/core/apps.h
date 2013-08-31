#ifndef APPS_H
#define APPS_H

#include <stdint.h>
#include "network.h"

typedef struct {
	void (*init)(void*);
	int8_t (*get)(struct packet_t*);
	void (*set)(struct packet_t*);
	void *cfg;
} application_t;


void apps_set(application_t* apps, uint8_t size);
application_t* app_get(uint8_t sensor);
void apps_setup(application_t* apps);
void apps_init();


#endif
