#include "text.h"

/* This device get a string : "helloworld" and write
   what he get on the uart */
int8_t text_get(struct data_t *data) {
	char *text = "hello";
	uint8_t len = strlen(text);
	uart_putstr_P(PSTR("text_get()\r\n"));
	if (data->remaining_len < (len+2)) return -1;   /* Not enough room */

	return set_data_string(data,text,len);
}

uint16_t text_set(struct data_t *data) {
	uint8_t xx;
	char buf[4];

	/* Source node */
	xx = get_node_src(data);
	itoa(xx,buf,10);
	uart_putstr(buf);
	uart_putstr_P(PSTR(","));
	/* Source device */
	xx = get_device_src(data);
	itoa(xx,buf,10);
	uart_putstr(buf);
	uart_putstr_P(PSTR(","));
	/* Data type */
	xx = get_data_type(data);
	itoa(xx,buf,10);
	uart_putstr(buf);
	uart_putstr_P(PSTR(","));
	/* Datas */
	/* XXX */

	uart_putstr_P(PSTR("\r\n"));
}

