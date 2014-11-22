#ifndef _TWI_H_
#define _TWI_H_


// Possible return states

// Number of retry when device does not answer
#define TWI_MAX_RETRY 5

enum {
	TW_SUCCESS,
	TW_UNKNOWN_ERROR,
	TW_UNEXPECTED,
	TW_ARBITRATION_FAILED,
	TW_NACK,
};

void twi_init();

int twi_nwrite(uint8_t addr, uint8_t *data, uint8_t n);

int twi_nread(uint8_t addr, uint8_t *data, uint8_t n);

#endif
