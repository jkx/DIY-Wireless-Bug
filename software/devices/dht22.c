// VERSION: 0.3.2
// PURPOSE: DHT11 Temperature & Humidity Sensor library for Arduino
// LICENSE: GPL v3 (http://www.gnu.org/licenses/gpl.html)
//
// DATASHEET: http://www.micro4you.com/files/sensor/DHT11.pdf
//
// HISTORY:
// George Hadjikyriacou - Original version (??)
// Mod by SimKard - Version 0.2 (24/11/2010)
// Mod by Rob Tillaart - Version 0.3 (28/03/2011)
// + added comments
// + removed all non DHT11 specific code
// + added references
// Mod by Nicolas Dupeux - Adapt to DHT22

#include "board.h"
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

#include "avr_compat.h"
#include "dht22.h"
#include "value.h"

int humidity;
int temperature;

#define DHT22 D,3

int dht22_read()
{
	// BUFFER TO RECEIVE
	uint8_t bits[5];
	uint8_t cnt = 7;
	uint8_t idx = 0;

	// EMPTY BUFFER
	for (int i=0; i< 5; i++) bits[i] = 0;

	// REQUEST SAMPLE
	drive(DHT22);
	clr_output(DHT22);
	_delay_ms(18);
	set_output(DHT22);
	_delay_us(40);
	tristate(DHT22);

	// ACKNOWLEDGE or TIMEOUT
	unsigned int loopCnt = 10000;
	while(get_input(DHT22) == 0)
		if (loopCnt-- == 0) return -2;

	loopCnt = 10000;
	while(get_input(DHT22) == 1)
		if (loopCnt-- == 0) return -2;

	// READ OUTPUT - 40 BITS => 5 BYTES or TIMEOUT
	for (int i=0; i<40; i++)
	{
		loopCnt = 10000;
		while(get_input(DHT22) == 0)
			if (loopCnt-- == 0) return -2;

		//unsigned long t = micros();

		//loopCnt = 10000;
		//while(get_input(DHT22) == 1)
		//	if (loopCnt-- == 0) return -2;

		//if ((micros() - t) > 40) bits[idx] |= (1 << cnt);
		_delay_us(45);
		if (get_input(DHT22) == 1)
			bits[idx] |= (1 << cnt);
		if (cnt == 0)   // next byte?
		{
			cnt = 7;    // restart at MSB
			idx++;      // next byte!
		}
		else cnt--;

		while(get_input(DHT22) == 1);
	}

	// WRITE TO RIGHT VARS
	humidity    = bits[0] * 256 + bits[1]; 
	temperature = (bits[2] & 0x7F) * 256 + bits[3]; 

	uint8_t sum = (bits[0] + +bits[1] + bits[2] + bits[3]) & 0xFF;  

	if (bits[4] != sum) {
		humidity=-1;
		temperature=-1;
		return -1;
	}
	return 0;
}

// DHT22 contains 2 sensors : temperature and humidity
// They are seens has 2 differents bugone devices
// Asking for temperature read the 2 values at once

int8_t dht22_humidity_read(struct packet_t *packet) {
	return set_data_int16(packet, humidity);
}

int8_t dht22_temperature_read(struct packet_t *packet) {
	dht22_read();

	return set_data_int16(packet, temperature);
}


