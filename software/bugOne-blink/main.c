#include "main.h"
#include <util/delay.h>


#define LED1   C,1
#define LED2   C,0


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
