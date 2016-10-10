#include "board.h"
#include <stdint.h>
#include <avr/io.h>
#include "adc.h"
#include "uart.h"
#include "photoresistor.h"
#include "value.h"

// Lecture d'une photoresistance branché sur l'ADC

void photoresistor_init(void *photoresistor_cfg) {
	adc_init(((photoresistor_cfg_s*)photoresistor_cfg)->adc_pin);
}

int8_t photoresistor_read(struct packet_t *packet) {
	uint16_t value;
	value = adc_read();
	return set_data_int16(packet, value);
}
