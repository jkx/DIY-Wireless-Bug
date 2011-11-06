#include "main.h"
#include "bugOne.h"
#include <util/delay.h>

#define LEDT1 B,5
#define LEDT2 B,4
#define LEDT3 B,3
#define LEDT4 B,2
#define LEDT5 B,1
#define LEDT6 B,0

int main( void )
{
  uint8_t delay = 50;
  sei();
  drive(LED1);
  drive(LED2);
  drive(LEDT1);
  drive(LEDT2);
  drive(LEDT3);


  while (1) 
  {
    _delay_ms(delay);
    toggle_output(LEDT1);
    _delay_ms(delay);
    toggle_output(LEDT2);
    _delay_ms(delay);
    toggle_output(LEDT3);
    _delay_ms(delay);
    toggle_output(LEDT4);
    _delay_ms(delay);
    toggle_output(LEDT5);
    _delay_ms(delay);
    toggle_output(LEDT6);
  }
}
