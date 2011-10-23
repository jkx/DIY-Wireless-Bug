#ifndef VALUE_H
#define VALUE_H

#define UNIT_CELSIUS 1
#define UNIT_VOLT 2

void send_value(uint8_t dst, int16_t value, int8_t pow, int8_t unit);

#include "config.h"

#endif
