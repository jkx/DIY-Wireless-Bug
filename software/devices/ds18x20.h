#ifndef DS18X20_H
#define DS18X20_H

#include "apps.h"

void ds18x20_init(void *cfg);
void ds18x20_test(void *cfg);
int8_t ds18x20_read(struct packet_t *packet);
int8_t ds18x20_read_id(struct packet_t *packet,uint8_t id[]);
void ds18x20_sleep(void);
void ds18x20_wakeup(void);


#endif
