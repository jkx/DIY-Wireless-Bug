#ifndef VALUE_H
#define VALUE_H

void set_devices(struct packet_t *packet, uint8_t device_src, uint8_t device_dst);
uint8_t get_device_src(struct packet_t *data);
uint8_t get_device_dst(struct packet_t *data);

uint8_t get_data_type(struct packet_t *packet);

uint8_t set_data_int16(struct packet_t *data, int16_t value);
int16_t get_data_int16(struct packet_t *packet);

uint8_t set_data_string(struct packet_t *data, char* str, uint8_t len);
#include "config.h"

#endif
