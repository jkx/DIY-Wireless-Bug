#ifndef DHT11_H
#define DHT11_H

#include "apps.h"

int8_t dht11_humidity_read(struct packet_t *packet);
int8_t dht11_temperature_read(struct packet_t *packet);

#endif
