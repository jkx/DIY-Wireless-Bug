#ifndef LED_H
#define LED_H

void led_init();
void led_set(struct packet_t *packet);
int8_t led_get(struct packet_t *packet);

#endif
