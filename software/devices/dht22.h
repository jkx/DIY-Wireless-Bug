#ifndef DHT22_H
#define DHT22_H

#include "apps.h"

int8_t dht22_humidity_read(struct packet_t *packet);
int8_t dht22_temperature_read(struct packet_t *packet);

#endif
