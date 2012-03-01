#ifndef BUTTON_H
#define BUTTON_H

void button_init(void* cfg);
int8_t button_read(struct packet_t *packet);

#endif
