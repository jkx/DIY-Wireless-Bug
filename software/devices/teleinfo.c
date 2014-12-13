#include <stdlib.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/pgmspace.h>


//#include "crc8.h"
#include "uart.h"
#include "teleinfo.h"

#include "avr_compat.h"
#include "board.h"
#include <util/delay.h>
#include "value.h"

teleinfo_values_t teleinfo;
uint16_t number_read = 64;
uint16_t registered_dev = 0;

// This function reads UART until it finds the "field" string of size n, 
// at start of a line (0xA in teleinfo protocol)
int teleinfo_find_field(char *field, uint8_t n)
{
	uint8_t i = 0;
	char a;
	//uart_putstr_P(PSTR("Wait start of line\r\n"));
	//while ((a = uart_getc()) != 0xA) {
	//	uart_putc(a & 0x7f); // Wait for new line
	//}
	//uart_putstr_P(PSTR("Wait field\r\n"));
	while (i < n) {
		a = uart_getc();
		if ((a & 0x7f) == field[i]) {
			i++;
		} else {
			i = 0;
		}
		uart_putc(a & 0x7f); // Wait for new line
	}
	return 0;
}

int teleinfo_store_field(char *field, uint8_t n)
{ 
	uint8_t i = 0;

	//uart_putstr_P(PSTR("Storing field\r\n"));
	for (i = 0; i < n; i++) {
		field[i] = uart_getc() & 0x7f;
	}
	return i;
}

void teleinfo_get_frame() 
{
	// Read UART until Start Text is found
	//while (uart_getc() != 0x2);
	// We are in a new frame : read each element
	// This works only for "HC" tarification
	// First field to read is ADCO
	//uart_putstr_P(PSTR("Waiting for ADCO field\r\n")); 
	teleinfo_find_field("ADCO ", 5);
	teleinfo_store_field(teleinfo.adco, 12);
#if TELEINFO_CHECK_DATA
	teleinfo_checksum(teleinfo.adco, 12);
#endif
	//uart_putstr_P(PSTR("Waiting for ISOUSC field\r\n")); 
	teleinfo_find_field("ISOUSC ", 7);
	teleinfo_store_field(teleinfo.isousc, 2);
#if TELEINFO_CHECK_DATA
	teleinfo_checksum(teleinfo.isousc, 2);
#endif
	//uart_putstr_P(PSTR("Waiting for HCHC field\r\n")); 
	teleinfo_find_field("HCHC ", 5);
	teleinfo_store_field(teleinfo.ind_hchc, 9);
#if TELEINFO_CHECK_DATA
	teleinfo_checksum(teleinfo.ind_hchc, 9);
#endif
	//uart_putstr_P(PSTR("Waiting for HCHP field\r\n")); 
	teleinfo_find_field("HCHP ", 5);
	teleinfo_store_field(teleinfo.ind_hchp, 9);
#if TELEINFO_CHECK_DATA
	teleinfo_checksum(teleinfo.ind_hchp, 9);
#endif
	//uart_putstr_P(PSTR("Waiting for PTEC field\r\n")); 
	teleinfo_find_field("PTEC ", 5);
	teleinfo_store_field(teleinfo.ptec, 4);
#if TELEINFO_CHECK_DATA
	teleinfo_checksum(teleinfo.ptec, 4);
#endif
	//uart_putstr_P(PSTR("Waiting for IINST field\r\n")); 
	teleinfo_find_field("IINST ", 6);
	teleinfo_store_field(teleinfo.iinst, 3);
#if TELEINFO_CHECK_DATA
	teleinfo_checksum(teleinfo.iinst, 3);
#endif
	//uart_putstr_P(PSTR("Waiting for IMAX field\r\n")); 
	teleinfo_find_field("IMAX ", 5);
	teleinfo_store_field(teleinfo.imax, 3);
#if TELEINFO_CHECK_DATA
	teleinfo_checksum(teleinfo.imax, 3);
#endif
	//uart_putstr_P(PSTR("Waiting for PAPP field\r\n")); 
	teleinfo_find_field("PAPP ", 5);
	teleinfo_store_field(teleinfo.papp, 5);
#if TELEINFO_CHECK_DATA
	teleinfo_checksum(teleinfo.papp, 5);
#endif
	number_read = 0;	
}

uint8_t teleinfo_checksum(char *s, uint8_t n)
{

	return 0;
}

void teleinfo_init(void *cfg) 
{
	registered_dev++;

#if O
	teleinfo = (teleinfo_values_t *)cfg;
	for (int i = 0; i < 16; i++) {
		if ((cfg & (1 << i)) != 0) {
			teleinfo_reader = (1 << i);
			break;
		}
	}
#endif
}



int8_t teleinfo_get_adco(struct packet_t *packet) {
	check_reader();
	return set_data_string(packet, teleinfo.adco, 12);
}

int8_t teleinfo_get_optarif(struct packet_t *packet) {
	check_reader();
	return set_data_string(packet, teleinfo.optarif, 4);
}

int8_t teleinfo_get_isousc(struct packet_t *packet) {
	check_reader();
	return set_data_string(packet, teleinfo.isousc, 2);
}

int8_t teleinfo_get_ind_hchc(struct packet_t *packet) {
	check_reader();
	return set_data_string(packet, teleinfo.ind_hchc, 9);
}

int8_t teleinfo_get_ind_hchp(struct packet_t *packet) {
	check_reader();
	return set_data_string(packet, teleinfo.ind_hchp, 9);
}

int8_t teleinfo_get_ptec(struct packet_t *packet) {
	check_reader();
	return set_data_string(packet, teleinfo.ptec, 4);
}

int8_t teleinfo_get_iinst(struct packet_t *packet) {
	check_reader();
	return set_data_string(packet, teleinfo.iinst, 3);
}

int8_t teleinfo_get_adps(struct packet_t *packet) {
	check_reader();
	return set_data_string(packet, teleinfo.adps, 3);
}

int8_t teleinfo_get_imax(struct packet_t *packet) {
	check_reader();
	return set_data_string(packet, teleinfo.imax, 3);
}

int8_t teleinfo_get_papp(struct packet_t *packet) {
	check_reader();
	return set_data_string(packet, teleinfo.papp, 5);
}

int8_t teleinfo_get_hhphc(struct packet_t *packet) {
	check_reader();
	return set_data_string(packet, teleinfo.hhphc, 1);
}

int8_t teleinfo_get_motdetat(struct packet_t *packet) {
	check_reader();
	return set_data_string(packet, teleinfo.motdetat, 6);
}


