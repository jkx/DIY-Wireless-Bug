#ifndef _SHT21_H_
#define _SHT21_H_

#include "apps.h"

typedef enum {
	SHT21Address = 0x80,
} SHT21_sensor;

typedef enum {
	TempHoldCmd        = 0xE3,
	RHumidityHoldCmd  = 0xE5,
	TempNoHoldCmd      = 0xF3,
	RHumidityNoHoldCmd = 0xF5,
} SHT21_cmds;

void sht2x_init(void *cfg);
int8_t sht2x_temp_read(struct packet_t *packet);
int8_t sht2x_hum_read(struct packet_t *);


#endif
