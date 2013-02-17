#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

#include "apps.h"

typedef struct {
	uint8_t adc_pin;
} photoresistor_cfg_s;

void photoresistor_init(void *photoresistor_cfg);
int8_t photoresistor_read(struct packet_t *data);

#endif
