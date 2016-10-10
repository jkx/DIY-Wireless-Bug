#ifndef ADC_H
#define ADC_H
#include <stdint.h>
#include <avr/io.h>

// Lecture d'un LM35 branché sur PC0

#define DEBUG

uint16_t adc_init(uint8_t pin);

uint16_t adc_read();

void adc_disable();

#endif
