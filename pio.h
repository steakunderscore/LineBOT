/** @file   pio.h
    @author M. P. Hayes, UCECE
    @date   11 Jan 2006
    @brief  PIO hardware abstraction for AVR microcontroller.
    @note   Macros and inline functions are used to avoid function
            call overhead and to allow compile-time constant folding. 
*/
#ifndef PIO_H
#define PIO_H

#include "config.h"

#define PIO_AVR

/** Define port names, note not all the ports are available on some AVRs.  */

#ifdef PORTA
#define PORT_A &PORTA
#endif

#ifdef PORTB
#define PORT_B &PORTB
#endif

#ifdef PORTC
#define PORT_C &PORTC
#endif

#ifdef PORTD
#define PORT_D &PORTD
#endif

#ifdef PORTE
#define PORT_E &PORTE
#endif

#ifdef PORTF
#define PORT_F &PORTF
#endif

#ifdef PORTG
#define PORT_G &PORTG
#endif


typedef volatile uint8_t *pio_port_t;
typedef uint8_t pio_mask_t;


typedef struct
{
    pio_port_t port;
    pio_mask_t bitmask;
} pio_t;


/* Define a PIO as a structure in terms of a port and a bitmask.  */
#define PIO_DEFINE(PORT, PORTBIT) (pio_t){PORT, BIT (PORTBIT)}


typedef enum pio_config_enum 
{
    PIO_INPUT = 1, PIO_OUTPUT, PIO_PULLUP
} pio_config_t;


/** DDR  PIO  Comment
     0     0  High impedance input
     0     1  Weak pullup input
     1     0  Output low
     1     1  Output high
*/


/** Private macro to map a pio to its corresponding data direction
   register (DDR).  NB, the DDR and PORT registers must be separated
   by the same number of bytes in all cases.  PORTB is used for the
   pattern since PORTA is not always defined for some AVRs.  */
#define PIO_DDR_(pio) (*(pio.port + (&DDRB - &PORTB)))

/** Private macro to map a pio to its input register (PIN).  NB, the
   PIN and PORT registers must be separated by the same number of
   bytes in all cases.  PORTB is used for the pattern since PORTA is
   not always defined for some AVRs.  */
#define PIO_PIN_(pio) (*(pio.port + (&PINB - &PORTB)))

/** Private macro to access a pio data register.  */
#define PIO_DATA_(pio) (*pio.port)


/** Configure pio.
    @param pio  */
static inline
bool pio_config_set (pio_t pio, pio_config_t config)
{
    switch (config)
    {
    case PIO_OUTPUT:
        PIO_DDR_ (pio) |= pio.bitmask;
        return 1;

    case PIO_INPUT:
        PIO_DDR_ (pio) &= ~pio.bitmask;
        PIO_DATA_ (pio) &= ~pio.bitmask;
        return 1;

    case PIO_PULLUP:
        PIO_DDR_ (pio) &= ~pio.bitmask;
        PIO_DATA_ (pio) |= pio.bitmask; 
        return 1;

    default:
        return 0;
    }
}


/** Set pio high.
    @param pio  */
static inline
void pio_output_high (pio_t pio)
{
    PIO_DATA_ (pio) |= pio.bitmask;
}


/** Set pio low. 
    @param pio  */
static inline
void pio_output_low (pio_t pio)
{
    PIO_DATA_ (pio) &= ~pio.bitmask;
}


/** Toggle pio.
    @param pio  */
static inline
void pio_output_toggle (pio_t pio)
{
    PIO_DATA_ (pio) ^= pio.bitmask;
}


/** Read input state from pio. 
    @param pio
    @return input state of pio  */
static inline
bool pio_input_get (pio_t pio)
{
    return (PIO_PIN_ (pio) & pio.bitmask) != 0;
}


/** Get output state of pio. 
    @param pio
    @return output state of pio  */
static inline
bool pio_output_get (pio_t pio)
{
    return (PIO_DATA_ (pio) & pio.bitmask) != 0;
}


/** Set pio to desired state
    @param pio
    @param state value to write pio  */
static inline
void pio_output_set (pio_t pio, bool state)
{
    state ? pio_output_high (pio) : pio_output_low (pio);
}


/** Enable the clock for the pio; nothing to do.  */
#define pio_init(pio)


/** Disable the clock for the pio; nothing to do.  */
#define pio_shutdown(pio)

#endif
