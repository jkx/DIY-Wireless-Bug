
/*

This is an minimal example howto use the watchdog, to put the bugOne
in deep sleep mode.

NOTE : In this state, the bugOne drains around 20uA, and can only send

*/






#include "bugOne.h"

#include <avr/interrupt.h>
#include <avr/power.h>
#include <stdlib.h>


#include "uart.h"
#include "config.h"
#include "rfm12.h"

// devices
#include "bandgap.h"
#include "const.h"




#define RFM12_USE_POWER_CONTROL 1


application_t applications[] = { 
    {bandgap_init,bandgap_get,NULL,NULL},
    {NULL,const_read,NULL,NULL},
    {NULL,NULL,NULL,NULL},
};


void my_sleep() {
    delay_500ms();
    rfm12_power_down();
    led_disable();
    bugone_deep_sleep();
}


// The watchdog wake us, what we do ?
SIGNAL(WDT_vect) {
    // tell the AVR to power devices
    power_all_enable();
    rfm12_power_up();
    // just blink
    led_setup();
    led_blink1();
}


void my_send()
{
    uint8_t i;
    struct packet_t *packet = get_tx_packet();

    application_t *application;
    int8_t len;
    i=0;
    while ( (application = app_get(i)) != NULL) {
        i++;
        if (application->get == NULL) {
            continue;
        }
        set_devices(packet,i,0x29);
        len=application->get(packet);
    }
    send(0xFF,6,packet);
    while (ctrl.txstate!=STATUS_FREE) {
        rfm12_tick();
        //delay_250ms();
    }
    uart_putstr_P(PSTR("send done ...\r\n"));
    led_blink2();
}


int main ( void )
{
    // cut & paste from the bugone_init() ..
    // note that timer1.init() cause the power_all_enable() to bug ..
    // and system randomly do some weird stuff ..
    uint8_t i=0;


    led_init();
    uart_init();
    rfm12_init();
    config_init();


    apps_setup(applications);
    apps_init();

    led_blink1();
    bugone_setup_watchdog(9);

    sei();
    uart_putstr_P(PSTR("Boot\r\n"));
    while (1) {
        my_send();
        my_sleep();
    }
}
