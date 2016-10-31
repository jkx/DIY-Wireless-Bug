/* This is the default project for bugone board
 * override with a project.h in your project directory
 */
#ifndef PROJECT_H
#define PROJECT_H

/**** UART DEBUGGING
 * en- or disable debugging via uart.
 */
#define RFM12_UART_DEBUG 0

/* control rate, frequency, etc during runtime
 * this setting will certainly add a bit code
 **/
#define RFM12_LIVECTRL 0
#define RFM12_NORETURNS 0
#define RFM12_USE_WAKEUP_TIMER 0
#define RFM12_TRANSMIT_ONLY 0
#define RFM12_MOSFET_PWR_CTRL 1

/* Disable interrupt vector and run purely inline. This may be useful for
 * configurations where a hardware interrupt is not available.
 */
#define RFM12_USE_POLLING 0
#define RFM12_NOCOLLISIONDETECTION 0
#define BUGONE_ANNOUNCE_SLEEP 1

#endif
