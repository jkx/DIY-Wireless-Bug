#ifndef LM35_H
#define LM35_H

#include "apps.h"

typedef struct {
	uint8_t adc_pin;
} lm35_cfg_s;

void lm35_init(lm35_cfg_s *lm35_cfg);
int8_t lm35_read(struct data_t *data);

#endif
