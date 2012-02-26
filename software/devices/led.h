#ifndef LED_H
#define LED_H

void led_init();
void led_set(struct data_t *data);
int8_t led_get(struct data_t *data);

#endif
