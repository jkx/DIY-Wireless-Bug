#ifndef VALUE_H
#define VALUE_H

uint8_t get_data_type(struct data_t *data);

uint8_t set_data_int16(struct data_t *data, int16_t value);
int16_t get_data_int16(struct data_t *data);

uint8_t set_data_string(struct data_t *data, char* str, uint8_t len);
#include "config.h"

#endif
