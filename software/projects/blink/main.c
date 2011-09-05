#include "main.h"
#include "bugOne.h"
#include <util/delay.h>


int main( void )
{
  sei();
  drive(LED1);
  drive(LED2);

  while (1) 
  {
    _delay_ms(100);
    toggle_output(LED1);
    _delay_ms(100);
    toggle_output(LED2);
  }
}
