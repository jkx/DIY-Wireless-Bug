#ifndef LM35_H
#define LM35_H

#include "apps.h"

typedef struct {
	uint8_t adc_pin;
} lm35_cfg_s;

void lm35_init(void *lm35_cfg);
int8_t lm35_read(struct packet_t *data);

#endif
