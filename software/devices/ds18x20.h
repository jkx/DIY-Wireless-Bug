#ifndef DS18X20_H
#define DS18X20_H

void ds18x20_init(void *cfg);
int8_t ds18x20_read(struct data_t *data);

#endif
