/*
 * Authors:
 *      Wim Looman
 *      Henry Jenkins
 *      Kate Markman
 *      Ben Snalam
 * Copyright:
 *      Copyright (c) 2010 Wim Looman, Henry Jenkins, Kate Markman, Ben Snalam
 * License:
 *      GNU General Public License (see LICENSE in root folder)
 */

// Include Standard files
#include "algorithm.h"
#include "config.h"
#include "constants.h"
#include "delay.h"
#include "motor.h"
#include "pio.h"
#include "sensor.h"
#include "target.h"

/* Software entry point
 */
int main(void) {
    volatile long int i;
    //s_initialise();
    DDRB |= 0x06;
    DDRD |= 0x0F;

    // Rotate Left
    PORTD &= 0xF9;
    PORTD |= 0x09;
    for (i = 100000; i > 0; i--) ;
    PORTB |= 0x06;

    for (i = 100000; i > 0; i--) ;
    
    // Stop
    PORTB &= 0xF9;
    for (i = 100000; i > 0; i--) ;

    // Rotate Right
    PORTD &= 0xF6;
    PORTD |= 0x06;
    for (i = 100000; i > 0; i--) ;
    PORTB |= 0x06;
}
