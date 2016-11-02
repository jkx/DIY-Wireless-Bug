#include <avr/io.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "network.h"
#include "avr_compat.h"
#include "rfm12.h"
#include "config.h"

#include "apps.h"
#include "value.h"

void set_devices(struct packet_t *packet, uint8_t device_src, uint8_t device_dst) {
	packet->payload[0] = device_src;
	packet->payload[1] = device_dst;

	packet->payload+=2;
}

uint8_t get_devices(struct packet_t *packet, uint8_t* device_src, uint8_t *device_dst) {
	uart_putstr_P(PSTR("get_devices\r\n"));
	if (get_remaining_length(packet) < 2) {
		uart_putstr_P(PSTR("ko\r\n"));
		return 0;
	}
	*device_src = packet->payload[0];
	*device_dst = packet->payload[1];
	
	uart_putstr_P(PSTR("dest: "));
	char buf[5];
	itoa(*device_dst,buf,10);
	uart_putstr(buf);
	uart_putstr_P(PSTR("\r\n"));
	uart_putstr_P(PSTR("src: "));
	itoa(*device_src,buf,10);
	uart_putstr(buf);
	uart_putstr_P(PSTR("\r\n"));

	packet->payload+=2;
	if ((*device_src == 0xFF) && (*device_dst == 0xFF)) {
		uart_putstr_P(PSTR("No more devices\r\n"));
		return 0;
	}
	return 1;
}

uint8_t get_device_src(struct packet_t *packet) {
	//return data->buf[-2];
}

uint8_t get_device_dst(struct packet_t *packet) {
	//return data->buf[-1];
}

uint8_t get_data_type(struct packet_t *packet) {
	uint8_t type=packet->payload[0];
	uart_putstr_P(PSTR("get_data_type\r\n"));
	uart_putstr_P(PSTR("type: "));
	uart_putc(type);
	uart_putstr_P(PSTR("\r\n"));
	packet->payload++;
	return type;
}

uint8_t set_data_int16(struct packet_t *packet, int16_t value) {
	char buf[5];
	itoa(value,buf,10);
	uart_putstr(buf);

	packet->payload[0]='I';
	packet->payload[1]=value & 0x00FF;
	packet->payload[2]=(value & 0xFF00) >> 8;

	packet->payload+=3;
	return 3;
}

int16_t get_data_int16(struct packet_t *packet) {
		uart_putstr_P(PSTR("get_data_int16\r\n"));
	int16_t value = packet->payload[0];
  	value |= (((uint16_t)packet->payload[1]*0xFF) << 8);

	uart_putstr_P(PSTR("value: "));
	char buf[5];
	itoa(value,buf,10);
	uart_putstr(buf);
	uart_putstr_P(PSTR("\r\n"));
	packet->payload+=2;
	return value;
}

uint8_t set_data_string(struct packet_t *packet, char* str, uint8_t len) {
	packet->payload[0]='S';
	packet->payload[1]=len;
	memcpy(packet->payload+2,str,len);

        packet->payload+=len+2;
	return len+2;
}
