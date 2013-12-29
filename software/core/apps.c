#include <stdint.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "apps.h"

static application_t* _apps;
static uint8_t _size;

void set_apps(application_t* apps, uint8_t size) {
	_apps = apps;
	_size = size;
}

application_t* get_app(uint8_t device) {
	if (device <= _size) 
		return &_apps[device];
	else
		return NULL;
}
