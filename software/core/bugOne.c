#include "bugOne.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include <avr/sleep.h>
#include <avr/power.h>

#include "avr_compat.h"
#include "rfm12.h"

#include "apps.h"
#include "config.h"

#ifndef PRG
#define PRG "unknown"
#endif

#ifdef BUGONE_HAS_CONFIG
static int8_t _conf_time = -1;
static int8_t _conf_current_time = 127;
#endif


void delay_1s() {
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
    _delay_ms(250);
}


void delay_500ms()
{
    _delay_ms(250);
    _delay_ms(250);
}

void delay_250ms()
{
    _delay_ms(250);
}

/* Initialise board */
void bugone_init(application_t* applications) {
    char buf[16];

#if defined(RFM12_MOSFET_PWR_CTRL)
    drive(MOSFET_PWR_PIN);
    clr_output(MOSFET_PWR_PIN);
#endif
    led_init();
    uart_init();
    rfm12_init();
    config_init();
    apps_setup(applications);

    uart_putstr_P(PSTR("\r\nFirmware version "));
    uart_putstr_P(PSTR(FWVERSION_STR));
    uart_putstr_P(PSTR(" for "));
    uart_putstr_P(PSTR(PRG));
    uart_putstr_P(PSTR("\r\n"));

    uart_putstr_P(PSTR("Node address : "));
    itoa(config.address,buf,10);
    uart_putstr(buf);
    uart_putstr_P(PSTR("\r\n"));

    apps_init();

    sei();
    uart_putstr_P(PSTR("bugOne init complete\r\n"));
    //clr_output(LED1);
    //clr_output(LED2);
}

#ifdef BUGONE_HAS_CONFIG
void bugone_set_config_period(int8_t conf_time) {
	_conf_time = conf_time;
}
#endif

extern application_t applications[];

volatile uint8_t send_flush=0;

void bugone_complete_sleep() {
#if BUGONE_ANNOUNCE_SLEEP
    struct packet_t *packet = get_tx_packet();
    send(0xFF, SLEEP, packet);
    while (ctrl.txstate!=STATUS_FREE) {
        rfm12_tick();
    } 
    led_blink2();
#endif
#if defined(RFM12_MOSFET_PWR_CTRL) && RFM12_MOSFET_PWR_CTRL
    rfm12_disable();
    // Pull up the MOSFET grid to power down the rfm12
    tristate(MOSFET_PWR_PIN);
    set_output(MOSFET_PWR_PIN);
#else
    rfm12_power_down();
#endif
    // To flush the UART
    delay_500ms();
}

void bugone_sleep() {
    clr_output(LED1);
    led_disable();
    bugone_deep_sleep();
}

void bugone_complete_wakeup() {
    power_all_enable();
#if defined(RFM12_MOSFET_PWR_CTRL) && RFM12_MOSFET_PWR_CTRL
    // Pull up the MOSFET grid to power down the rfm12
    drive(MOSFET_PWR_PIN);
    clr_output(MOSFET_PWR_PIN);
    delay_250ms();
    rfm12_init();
#else
    rfm12_power_up();
    delay_250ms();
#endif
}

void bugone_wakeup() {
    led_setup();
    set_output(LED1);
}

void bugone_send() {
    struct packet_t *packet = get_tx_packet();
    application_t *application;
    int8_t len;
    uint8_t i;
    uart_putstr_P(PSTR("\r\n"));
    i=0;
    while ( (application = app_get(i)) != NULL) {
        i++;
		  if (application->sleeptime >= 0) {
			  if (application->current_time >= application->sleeptime) { 
				  uart_putstr_P(PSTR("#"));
				  if (application->get == NULL) {
					  continue;
				  }
				  set_devices(packet,i,0x29);
				  len=application->get(packet);
				  if (len > 0) {
					  //data.remaining_len-=len;
					  //data.buf+=len;
				  }
				  application->current_time = 0;
			  } else {
				  application->current_time++;
			  }
		  }
    }
    send(0xFF,6,packet);

	 while (ctrl.txstate!=STATUS_FREE) {
		 rfm12_tick();
	 } 

#ifdef BUGONE_HAS_CONFIG
	 if (_conf_time >= 0) {
		 if (_conf_current_time >= _conf_time) {
			 packet = get_tx_packet();
			 send_config(0xFF,packet);
			 _conf_current_time = 0;
			 while (ctrl.txstate!=STATUS_FREE) {
				 rfm12_tick();
			 } 
		 }	else {
			 _conf_current_time++;
		 } 
	 }
#endif 

    // RFM12 managment
}

void bugone_receive() { 
    uint8_t *bufcontents;

    // RFM12 managment
    while ((ctrl.txstate != STATUS_FREE) || (rfm12_rx_status() == STATUS_COMPLETE)) {
		 while (ctrl.txstate != STATUS_FREE) {
			 rfm12_tick();
		 }
		 delay_250ms();
		 if (rfm12_rx_status() == STATUS_COMPLETE) {
			 bufcontents=rfm12_rx_buffer();
			 recv(bufcontents);
			 //led_blink2();
		 }
    } 
}

void bugone_send_receive() {
	 bugone_send();
	 bugone_receive();
}


void bugone_loop() {
    uint8_t *bufcontents;

    // RFM12 managment
    while (ctrl.txstate!=STATUS_FREE) {
        rfm12_tick();
    } 

#if !(RFM12_TRANSMIT_ONLY)
    if (rfm12_rx_status() == STATUS_COMPLETE) {
        bufcontents=rfm12_rx_buffer();
        recv(bufcontents);
    }
#endif

    // Every minutes
    //uart_putstr_P(PSTR("."));
    if (send_flush == 1) {
        uart_putstr_P(PSTR("Send.."));
        bugone_send();
        send_flush=0;
    }
}


//****************************************************************
// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
// for more infos check this
// http://interface.khm.de/index.php/lab/experiments/sleep_watchdog_battery/
// WARNING : you must implement SIGNAL(WDT_vect) if you use this
void bugone_setup_watchdog(int val) {
    unsigned char  bb;
    if (val > 9 ) val=9;
    bb=val & 7;
    if (val > 7) bb|= (1<<5);
    bb|= (1<<WDCE);

    MCUSR &= ~(1<<WDRF);
    // start timed sequence
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    // set new watchdog timeout value
    WDTCSR = bb;
    WDTCSR |= _BV(WDIE);
}


void bugone_deep_sleep() {
    power_all_disable();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // set sleep mode and enable
    sleep_enable();
    sleep_mode();                        // let's sleep and wake-up
    sleep_disable();
}

