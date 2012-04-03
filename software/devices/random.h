#ifndef RANDOM_H
#define RANDOM_H

#include "apps.h"

void random_init(void *);
int8_t random_read(struct packet_t *data);

#endif
