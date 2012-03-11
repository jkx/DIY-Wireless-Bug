#ifndef DS18X20_H
#define DS18X20_H

#include "apps.h"

void ds18x20_init(void *cfg);
int8_t ds18x20_read(struct packet_t *packet);

#endif
