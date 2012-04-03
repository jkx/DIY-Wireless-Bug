#include "board.h"
#include <stdint.h>
#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"
#include "random.h"
#include "value.h"

// Return a very (!) pseudo random value between 0 and 100 every read()

#define DEBUG

void random_init(void *unused) {
	// Init seed
	srand(4);
}

int8_t random_read(struct packet_t *packet) {
	int16_t value = rand() / (RAND_MAX / 100 + 1);
	return set_data_int16(packet, value);
}
