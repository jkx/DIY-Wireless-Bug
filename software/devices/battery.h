#ifndef BATTERY_H
#define BATTERY_H

typedef struct {
	uint8_t compute_voltage;
} bat_cfg_t;


void   battery_init(void*);
void   battery_disable();
int8_t battery_get(struct packet_t *packet);

#endif
