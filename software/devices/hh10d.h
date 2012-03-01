#ifndef HH10D_H
#define HH10D_H

#include "apps.h"

void hh10d_init(void*);
void hh10d_freq(void);
int8_t hh10d_read(struct packet_t *packet);

#endif
