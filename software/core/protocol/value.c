#include <avr/io.h>
#include <string.h>
#include "network.h"
#include "avr_compat.h"
#include "rfm12.h"
#include "config.h"

#include "apps.h"
#include "value.h"

void set_devices(struct data_t *data, uint8_t device_src, uint8_t device_dst) {
	data->buf[0] = device_src;
	data->buf[1] = device_dst;
}

uint8_t get_device_src(struct data_t *data) {
	return data->buf[-2];
}

uint8_t get_device_dst(struct data_t *data) {
	return data->buf[-1];
}

uint8_t get_data_type(struct data_t *data) {
	return data->buf[0];
}

uint8_t set_data_int16(struct data_t *data, int16_t value) {
	char buf[5];
	itoa(value,buf,10);
	uart_putstr(buf);

	data->buf[0]='I';
	data->buf[1]=value & 0x00FF;
	data->buf[2]=(value & 0xFF00) >> 8;

	return 3;
}

int16_t get_data_int16(struct data_t *data) {
	return data->buf[1]+data->buf[0]*0xFF;
}

uint8_t set_data_string(struct data_t *data, char* str, uint8_t len) {
	data->buf[0]='S';
	data->buf[1]=len;
	memcpy(data->buf+2,str,len);

	return len+2;
}
