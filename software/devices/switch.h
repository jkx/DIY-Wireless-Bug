#ifndef SWITCH_H
#define SWITCH_H

#define RELAY_PIN B,2

void switch_init();
int8_t switch_set(struct packet_t *packet);
int8_t switch_get(struct packet_t *packet);

#endif
