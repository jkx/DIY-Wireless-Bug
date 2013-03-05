#ifndef LED_H
#define LED_H

void led_init();
void led_set(struct packet_t *packet);
int8_t led_get(struct packet_t *packet);
void led_setup();
void led_disable();
void led_blink1();
void led_blink2();

#endif
