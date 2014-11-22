#include <stdlib.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/pgmspace.h>


//#include "crc8.h"
#include "twi.h"
#include "sht2x.h"

#include "avr_compat.h"
#include "board.h"
#include <util/delay.h>
#include "value.h"


void sht2x_init(void *cfg) {
	
}

int8_t sht2x_temp_read(struct packet_t *packet) {
	uint16_t temperature;
	uint8_t temp[3];
	float temperatureC;
	int8_t command = TempNoHoldCmd;

	twi_init();

	// Request temp measure
	//
	if (twi_nwrite(SHT21Address, &command, 1) != TW_SUCCESS) {
		return -128;
	}
	_delay_ms(100);   
	if (twi_nread(SHT21Address, temp, 3) != TW_SUCCESS) {
		return -128;
	}
	temperature = temp[0] << 8;
	temperature += temp[1];
	temperatureC =  (((175.72/65536.0) * (float)temperature) - 46.85); //T= -46.85 + 175.72 * ST/2^16

	return set_data_int16(packet, (int) (temperatureC*10));
}

int8_t sht2x_hum_read(struct packet_t *packet) {
	uint16_t humidity;
	uint8_t hum[3];
	float humidityRH;
	int8_t command = RHumidityNoHoldCmd;

	twi_init();

	// Request humidity measure
	//
	if (twi_nwrite(SHT21Address, &command, 1) != TW_SUCCESS) {
		return -128;
	}
	_delay_ms(100);   
	if (twi_nread(SHT21Address, hum, 3) != TW_SUCCESS) {
		return -128;
	}
	humidity = hum[0] << 8;
	humidity += hum[1];
	humidityRH = -6.0 + 125.0/65536.0 * (float)humidity;       // RH= -6 + 125 * SRH/2^16

	return set_data_int16(packet, (int) (humidityRH*10));
}
