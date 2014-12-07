/* 
 * I2C (two wire) interface library
 * Inspired from Arduino Wire library
 * Two modes are available:
 *  - polling mode, in which pin state must be polled
 *  - interrupt mode, communication is initiated and then everything is
 *  managed through interrupts
 */

#include "board.h"

#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <util/twi.h>

#include "twi.h"


void twi_init()
{
    TWSR = 0;
    // Bitrate : 100kHz
    TWBR = (F_CPU / 100000UL - 16) / 2;
}

int twi_nwrite(uint8_t addr, uint8_t *data, uint8_t n)
{
    int8_t nb_st = 0;
    // Start I2C comm
restart:
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    // Wait for completion
    while ((TWCR & _BV(TWINT)) == 0);
    switch(TWSR) {
        case 0x8:
        case 0x10:
            break;
        case 0x38:
            TWCR = _BV(TWEN) | _BV(TWSTO) | _BV(TWINT);
            return TW_UNEXPECTED;
        default:
            return TW_UNKNOWN_ERROR;
    }
    
    // Send slave address with write bit set
    TWDR = addr | TW_WRITE;
    TWCR = _BV(TWINT) | _BV(TWEN);
    while ((TWCR & _BV(TWINT)) != _BV(TWINT));
    switch (TWSR) {
        case 0x20:
            if (nb_st < TWI_MAX_RETRY) {
                nb_st++;
                goto restart;
            } else {
                TWCR = _BV(TWEN) | _BV(TWSTO) | _BV(TWINT);
                return TW_NACK;
            }
        case 0x18:
            break;
        case 0x38:
            TWCR = _BV(TWEN) | _BV(TWSTO) | _BV(TWINT);
            return TW_ARBITRATION_FAILED;
        default:
            return TW_UNKNOWN_ERROR;
    }

    // Send n data bytes
    for (int i = 0; i < n; i++) {
        TWDR = data[i];
        TWCR = _BV(TWINT) | _BV(TWEN);
        while ((TWCR & _BV(TWINT)) != _BV(TWINT));
        switch (TWSR) {
            case 0x30:
            case 0x28:
                break;
            case 0x38:
                TWCR = _BV(TWEN) | _BV(TWSTO) | _BV(TWINT);
                return TW_ARBITRATION_FAILED;
            default:
                return TW_UNKNOWN_ERROR;
        }
    }

    // Everything OK, send STOP
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
    return TW_SUCCESS;
}

int twi_nread(uint8_t addr, uint8_t *data, uint8_t n)
{
    // Start I2C comm
    int8_t nb_st = 0;
restart_rd:
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    // Wait for completion
    while ((TWCR & _BV(TWINT)) != _BV(TWINT));
    if ((TWSR != 0x8) && (TWSR != 0x10))
        return TW_UNEXPECTED;
    // START sent
    
    // Send slave address with write bit set
    TWDR = addr | TW_READ;
    TWCR = _BV(TWINT) | _BV(TWEN);
    while ((TWCR & _BV(TWINT)) != _BV(TWINT));
    // Three possible values
    switch (TWSR) {
        case 0x48:
            if (nb_st < TWI_MAX_RETRY) {
                nb_st++;
                goto restart_rd;
            } else {
                TWCR = _BV(TWEN) | _BV(TWSTO) | _BV(TWINT);
                return TW_NACK;
            }
            return TW_NACK;
        case 0x40:
            break;
        case 0x38:
            TWCR = _BV(TWEN) | _BV(TWSTO) | _BV(TWINT);
            return TW_ARBITRATION_FAILED;
        default:
            return TW_UNKNOWN_ERROR;
    }

    // Receive n data bytes
    for (int i = 0; i < n-1; i++) {
        TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
        while ((TWCR & _BV(TWINT)) != _BV(TWINT));
        data[i] = TWDR;
        switch (TWSR) {
            case 0x50:
                // Data byte received and ACK returned
                break;
            case 0x58:
                // Data byte received and NACK returned (unexpected)
                TWCR = _BV(TWEN) | _BV(TWSTO) | _BV(TWINT);
                return TW_NACK;
            case 0x38:
                TWCR = _BV(TWEN) | _BV(TWSTO) | _BV(TWINT);
                return TW_ARBITRATION_FAILED;
            default:
                return TW_UNKNOWN_ERROR;
        }
    }
    TWCR = _BV(TWINT) | _BV(TWEN);
    while ((TWCR & _BV(TWINT)) != _BV(TWINT));
    data[n-1] = TWDR;
    switch (TWSR) {
        case 0x50:
            // Data byte received and ACK returned (unexepected)
            TWCR = _BV(TWEN) | _BV(TWSTO) | _BV(TWINT);
            return TW_UNEXPECTED;
            break;
        case 0x58:
            // Data byte received and NACK returned
            TWCR = _BV(TWEN) | _BV(TWSTO) | _BV(TWINT);
            return TW_SUCCESS;
        case 0x38:
            TWCR = _BV(TWEN) | _BV(TWSTO) | _BV(TWINT);
            return TW_ARBITRATION_FAILED;
        default:
            return TW_UNKNOWN_ERROR;
    }
}
