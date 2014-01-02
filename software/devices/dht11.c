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

#include "board.h"
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

#include "avr_compat.h"
#include "dht11.h"
#include "value.h"

#include <avr/pgmspace.h>

int humidity;
int temperature;

#define DHT11 B,2

int dht11_read()
{
	// BUFFER TO RECEIVE
	uint8_t bits[5];
	uint8_t cnt = 7;
	uint8_t idx = 0;

	// EMPTY BUFFER
	for (int i=0; i< 5; i++) bits[i] = 0;

	// REQUEST SAMPLE
	drive(DHT11);
	clr_output(DHT11);
	_delay_ms(18);
	set_output(DHT11);
	_delay_us(40);
	tristate(DHT11);

	// ACKNOWLEDGE or TIMEOUT
	unsigned int loopCnt = 10000;
	while(get_input(DHT11) == 0)
		if (loopCnt-- == 0) return -2;

	loopCnt = 10000;
	while(get_input(DHT11) == 1)
		if (loopCnt-- == 0) return -3;

	// READ OUTPUT - 40 BITS => 5 BYTES or TIMEOUT
	for (int i=0; i<40; i++)
	{
		loopCnt = 10000;
		while(get_input(DHT11) == 0)
			if (loopCnt-- == 0) return -4;

		//unsigned long t = micros();

		//loopCnt = 10000;
		//while(get_input(DHT11) == 1)
		//	if (loopCnt-- == 0) return -2;

		//if ((micros() - t) > 40) bits[idx] |= (1 << cnt);
		_delay_us(45);
		if (get_input(DHT11) == 1)
			bits[idx] |= (1 << cnt);
		if (cnt == 0)   // next byte?
		{
			cnt = 7;    // restart at MSB
			idx++;      // next byte!
		}
		else cnt--;

		while(get_input(DHT11) == 1);
	}

	// WRITE TO RIGHT VARS
        // as bits[1] and bits[3] are always zero they are omitted in formulas.
	humidity    = bits[0]; 
	temperature = bits[2]; 

	uint8_t sum = bits[0] + bits[2];  

	if (bits[4] != sum) {
		humidity=-1;
		temperature=-1;
		return -1;
	}
	return 0;
}

// DHT11 contains 2 sensors : temperature and humidity
// They are seens has 2 differents bugone devices
// Asking for temperature read the 2 values at once

int8_t dht11_humidity_read(struct packet_t *packet) {
	return set_data_int16(packet, humidity);
}

int8_t dht11_temperature_read(struct packet_t *packet) {
	dht11_read();
	return set_data_int16(packet, temperature);
}


int dht11_humidity_val() {
  return humidity;
}

int dht11_temperature_val() {
  dht11_read();
  return temperature;
}
