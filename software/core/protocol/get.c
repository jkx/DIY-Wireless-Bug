#include <avr/io.h>
#include <string.h>
#include "network.h"
#include "avr_compat.h"
#include "rfm12.h"
#include "config.h"

#include "uart.h"
#include "apps.h"

#ifdef BUGONE_HAS_CONFIG
void send_config(uint8_t dst, struct packet_t *packet) {
    application_t *application;
	 uint8_t i = 0;
	 uint8_t sz = 1;
	 char buf[256];
	 while ( (application = app_get(i)) != NULL ) {
		 i++;
		 buf[sz++] = i;
		 buf[sz++] = application->type;
	 }
	 buf[0] = i;
	 memcpy(packet->payload,buf,sz);
	 packet->payload+=sz;
	 send(dst,CONFIG,packet);
}
#endif

#ifdef BUGONE_HAS_CONFIG
void recv_get_config(struct packet_t *packet) {
	struct packet_t *send_packet = get_tx_packet();
	send_config(packet->network->src,send_packet);
}
#endif

void recv_get(struct packet_t *packet) {
	uint8_t device_src,device_dst;
	uint8_t len;
	application_t* app;

	struct packet_t *send_packet = get_tx_packet();

	while (get_devices(packet,&device_src,&device_dst)) {
		app=app_get(device_dst);
		set_devices(send_packet,device_dst,device_src);
		len=app->get(send_packet);
	//	if (len > 0) {
	//		data.remaining_len-=len;
	//	}
	}
	send(packet->network->src,VALUE,send_packet);
}


void send_get(uint8_t dst, uint8_t device) {
	uart_putstr_P(PSTR("send_get()\r\n"));
	char buf[2];
	buf[0]=0xFF;
	buf[1]=device;
	//send(dst,GET,buf,sizeof(buf));
}

void send_set(uint8_t dst, uint8_t device, int16_t value) {
	uart_putstr_P(PSTR("send_set()\r\n"));
	struct packet_t *packet=get_tx_packet();
	set_devices(packet,0xff,device);
	set_data_int16(packet,value);
	send(dst,SET,packet);
}

void recv_set(struct packet_t *packet) {
	uint8_t device_src,device_dst;
	application_t* app;
	uart_putstr_P(PSTR("recv_set()\r\n"));

	while (get_devices(packet,&device_src,&device_dst) == 1) {
		app=app_get(device_dst-1);
		if (app == NULL) continue; 
		if (app->set == NULL) continue;
		app->set(packet);
	}
}
