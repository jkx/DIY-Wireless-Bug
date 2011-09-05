/* vim: set sw=8 ts=8 si : */
/****************************************************************************
* Title   :   compatibility module for forward compatibility with
              newer ARV C compiler which does not have older
	      macros
* Authors:    Guido Socher
* Copyright: GPL
*
*        
*****************************************************************************/
#ifndef AVR_COMPAT_H
#define AVR_COMPAT_H


#define uchar unsigned char
#define uint unsigned int
#define bit uchar


#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#ifndef inb
#define inb(sfr) _SFR_BYTE(sfr) 
#endif

#ifndef outb
#define outb(sfr, val) (_SFR_BYTE(sfr) = (val))
#endif

#ifndef inw
#define inw(sfr) _SFR_WORD(sfr)
#endif

#ifndef outw
#define outw(sfr, val) ( _SFR_WORD(sfr) = (val)) 
#endif

#ifndef outp
#define outp(val, sfr) outb(sfr, val) 
#endif

#ifndef inp
#define inp(sfr) inb(sfr) 
#endif

#ifndef BV
#define BV(bit) _BV(bit)
#endif

/* compatibility macro for libc 1.0 to 1.2 */
#ifndef PRG_RDB
#define PRG_RDB(addr)       pgm_read_byte(addr)
#endif

#define nop()           asm volatile("nop")



// several macros .. 
#define BIT(p,b)                (b)

#define PORT(p,b)               (PORT ## p)
#define PIN(p,b)                (PIN ## p)
#define DDR(p,b)                (DDR ## p)

#define MASK(b)                 (1 << (b))


#define set_port_bit(p,b)       ((p) |= MASK(b))
#define clr_port_bit(p,b)     ((p) &= ~MASK(b))
#define get_port_bit(p,b)       (((p) & MASK(b)) != 0)
#define tgl_port_bit(p,b)    ((p) ^= MASK(b))


// main macro to use
#define set_output(io)          set_port_bit(PORT(io),BIT(io))
#define clr_output(io)        clr_port_bit(PORT(io),BIT(io))
#define get_output(io)          get_port_bit(PORT(io),BIT(io))
#define toggle_output(io)       tgl_port_bit(PORT(io),BIT(io))

#define get_input(io)           get_port_bit(PIN(io),BIT(io))


#define tristate(io)            clr_port_bit(DDR(io),BIT(io))
#define drive(io)               set_port_bit(DDR(io),BIT(io))


#endif //AVR_COMPAT_H


