#ifndef BANDGAP_H
#define BANDGAP_H

void   bandgap_init(void*);
void   bandgap_disable();
int   bandgap_read();
int8_t bandgap_get(struct packet_t *packet);

#endif
