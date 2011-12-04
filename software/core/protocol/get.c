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
	uint8_t sensor;
	int16_t value;
	struct network_t* network=(struct network_t*)payload;
	application_t* apps;

	sensor=*(uint8_t*)(network->payload);

	application_t* app=get_app(sensor);
	//value=app->get();
	//send_value(network->src,value,1,2);
}

void send_get(uint8_t dst, uint8_t sensor) {
	uart_putstr_P(PSTR("send_get()\r\n"));
	send(dst,GET,(char*)&sensor,1);
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
