#ifndef BOARD_H
#define BOARD_H

/* CPU frequency */
#define F_CPU 8000000

/* Pinout of leds */
#define LED1 C,1
#define LED2 C,0

/* UART baud rate. Use the speed with the lowest error rate */
#define UART_BAUD_RATE 38400

//Pin that the RFM12's slave select is connected to
#define DDR_SS DDRD
#define PORT_SS PORTD
#define BIT_SS 7

//SPI port
#define DDR_SPI DDRB
#define PORT_SPI PORTB
#define PIN_SPI PINB
#define BIT_MOSI 3
#define BIT_MISO 4
#define BIT_SCK  5
#define BIT_SPI_SS 2
//this is the hardware SS pin of the AVR - it 
//needs to be set to output for the spi-interface to work 
//correctly, independently of the CS pin used for the RFM12

#define MOSFET_PWR_PIN B,7
#define DDR_MOSFET_PWR DDRB
#define PORT_MOSFET_PWR PORTB
#define BIT_MOSFET_PWR 7

#endif
