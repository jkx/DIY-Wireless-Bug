/**** RFM 12 library for Atmel AVR Microcontrollers *******
 * 
 * This software is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 *
 * @author Peter Fuhrmann, Hans-Gert Dahmen, Soeren Heisrath
 */

/******************************************************
 *                                                    *
 *           C O N F I G U R A T I O N                *
 *                                                    *
 ******************************************************/

/*
	Connect the RFM12 to the AVR as follows:

	RFM12           | AVR
	----------------+------------
	SDO             | MISO
	nIRQ            | INT0
	FSK/DATA/nFFS   | VCC
	DCLK/CFIL/FFIT  |  -
	CLK             |  -
	nRES            |  -
	GND             | GND
	ANT             |  -
	VDD             | VCC
	GND             | GND
	nINT/VDI        | -
	SDI             | MOSI
	SCK             | SCK
	nSEL            | Slave select pin defined below
*/

#include "board.h"
#include "project.h"

//frequency to use
#define FREQ 868000000UL
#define RFM12_BASEBAND RFM12_BAND_868

//use this for datarates >= 2700 Baud
#define DATARATE_VALUE RFM12_DATARATE_CALC_HIGH(19200.0)

//use this for 340 Baud < datarate < 2700 Baud
//#define DATARATE_VALUE RFM12_DATARATE_CALC_LOW(1200.0)

/**** TX BUFFER SIZE
 */
#define RFM12_TX_BUFFER_SIZE 32

/**** RX BUFFER SIZE
 * there are going to be 2 Buffers of this size
 * (double_buffering)
 */
#define RFM12_RX_BUFFER_SIZE 32

/**** INTERRUPT VECTOR
 * define the interrupt vector settings here
 */
 
//the interrupt vector
#define RFM12_INT_VECT (INT0_vect)

//the interrupt mask register
#define RFM12_INT_MSK EIMSK

//the interrupt bit in the mask register
#define RFM12_INT_BIT (INT0)

//the interrupt flag register
#define RFM12_INT_FLAG EIFR

//the interrupt bit in the flag register
#define RFM12_FLAG_BIT (INTF0)

//setup the interrupt to trigger on negative edge
#define RFM12_INT_SETUP()   EICRA |= (1<<ISC01)
