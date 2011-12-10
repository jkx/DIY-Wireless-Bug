#include <avr/io.h>
#include <string.h>
#include "network.h"
#include "avr_compat.h"
#include "rfm12.h"
#include "config.h"

#include "uart.h"
#include "apps.h"

struct set_t {
	uint8_t sensor;
	int16_t value;
};

void recv_get(char* payload) {
	uint8_t device_src,device_dst;
	struct network_t* network=(struct network_t*)payload;
	char buf[28];
	uint8_t len;
	application_t* app;
	struct data_t data;

	data.buf=buf;
	data.packet=buf;
	data.remaining_len=sizeof(buf);

	while ((device_src != 0xFF) && (device_dst != 0xFF)) {
		app=get_app(device_dst);
		set_devices();
		len=app->get(&data);
		if (len > 0) {
			data.remaining_len-=len;
		}
	}
	send(network->src,VALUE,buf,26);
}

void send_get(uint8_t dst, uint8_t device) {
	uart_putstr_P(PSTR("send_get()\r\n"));
	char buf[2];
	buf[0]=0xFF;
	buf[1]=device;
	send(dst,GET,buf,sizeof(buf));
}

void send_set(uint8_t dst, uint8_t sensor, int16_t value) {
	uart_putstr_P(PSTR("send_set()\r\n"));
	struct set_t set;
	set.sensor=sensor;
	set.value=value;
	send(dst,SET,(char*)&set,sizeof(struct set_t));
}

void recv_set(char* payload) {
	struct network_t* network=(struct network_t*)payload;
	application_t* apps;
	uart_putstr_P(PSTR("recv_set()\r\n"));

	struct set_t* set;
	set=(struct set_t*)(network->payload);
	application_t* app=get_app(set->sensor);
	if (app != NULL)
		app->set(set->value);
}
