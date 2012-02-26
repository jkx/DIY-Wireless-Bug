#ifndef DHT11_H
#define DHT11_H

#include "apps.h"

int8_t dht11_humidity_read(struct data_t *data);
int8_t dht11_temperature_read(struct data_t *data);

#endif
