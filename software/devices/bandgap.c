/* 
   bugOne bandgap driver
   =====================
   Caution : the module enable the ADC, and never disable it.

*/


#include "bugOne.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "avr_compat.h"
#include "bandgap.h"


void bandgap_init(void *cfg) {
  // The first 2 calls return some noise
  getInternal_1v1();
  getInternal_1v1();
}


int getInternal_1v1(void){
  ADMUX = 0x4E;                // Sélectionne la référence interne à 1v1 
  ADCSRA |= (1 << ADEN);       // Active le convertisseur analogique -> numérique
  ADCSRA |= (1 << ADSC);       // Lance une conversion analogique -> numérique
  while(ADCSRA & (1 << ADSC)); // Attend la fin de la conversion
  return ADCL | (ADCH << 8);   // Récupére le résultat de la conversion
}


void bandgap_disable() {
  ADCSRA = 0;    // disable ADC
}

// return the bandgap value 
// to transform it to volt : (1023 * 1.1) / value
// for additionnal info check out : 
// http://skyduino.wordpress.com/2012/08/08/arduinoavr-mesurer-la-tension-reel-en-vcc/ 
int8_t bandgap_get(struct packet_t *packet) {
	uart_putstr_P(PSTR("bandgap_get\r\n"));
	return set_data_int16(packet,getInternal_1v1());
}

