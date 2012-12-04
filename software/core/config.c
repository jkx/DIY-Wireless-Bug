#include <avr/eeprom.h>

#include <config.h>

struct config_t config;

void config_init() {
	eeprom_read_block(&config,(const void*)0,sizeof(struct config_t));
}
