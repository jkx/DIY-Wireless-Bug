
/* 

This is a really minimal skel : no wireless, just LEDs en UART.

I2C>[0xa2 0x0a [0xa3 r:4
NACK
I2C START BIT
WRITE: 0xA2 ACK 
WRITE: 0x0A ACK 
I2C START BIT
WRITE: 0xA3 ACK 
READ: 0x01  ACK 0x6C  ACK 0x1D  ACK 0x36 

==
sens = 0x016C
offs = 0x1D36



*/


#include "bugOne.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>


#include "avr_compat.h"
#include "uart.h"
#include "config.h"
#include <stdio.h>



#define TCNT1_VAL 65536 - (F_CPU / 256)


int cnt;
int old_cnt;



ISR(INT1_vect)
{
  cnt ++;
}



ISR(TIMER1_OVF_vect)
{
  old_cnt = cnt;
  TCNT1=TCNT1_VAL; // set initial value to remove time error (16bit counter register)
  cnt = 0;
}


void init_hh10d()
{

  cbi(DDRD,PD3); // pin is input
  cbi(DDRD,PD3); // disable pullup

  // rising edge
  sbi(EICRA,ISC11);
  sbi(EICRA,ISC10);

  // enable INT1
  sbi(EIMSK,INT1);


  // setup timer1
  TIMSK1=0x01; // enabled global and timer overflow interrupt;
  TCCR1A = 0x00; // normal operation page 148 (mode0);
  TCNT1= TCNT1_VAL; // set initial value to remove time error (16bit counter register)
  sbi(TCCR1B,CS12); // prescaler set to /256
  cbi(TCCR1B,CS11);
  cbi(TCCR1B,CS10);
}




int main ( void )
{
  char buf[20];
  char val[7];
  double RH;


  drive(LED1);
  drive(LED2);

  set_output(LED1);
  set_output(LED2);
	
  uart_init();
  init_hh10d();
  sei();

  uart_putstr_P(PSTR("AVR init complete\r\n"));

  while (1) {

    toggle_output(LED2);
    _delay_ms(1000);

    RH = (0x1E68 - (double) old_cnt) * 0x018B / 4096;  
    //RH = (0x1D36 - (double) old_cnt) * 0x016C / 4096;

    sprintf(buf,"RH:%0.2f",RH);
    uart_putstr(buf);


    sprintf(buf,"[%d]\n",old_cnt);
    uart_putstr(buf);
  }
}
