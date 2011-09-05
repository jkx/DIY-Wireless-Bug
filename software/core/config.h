#ifndef CONFIG_H
#define CONFIG_H

#define FWVERSION "0.0.1"

void config_init();

struct config_t {
	uint8_t address;
	uint8_t key[16];
};

extern struct config_t config;

#endif
