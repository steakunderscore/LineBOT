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
#include "motor.h"
#include "pio.h"
#include "sensor.h"
#include "target.h"
#include <util/delay.h>

/* Software entry point
 */
int main(void) {
    DDRB |= 1;
    PORTB |= 1;
    m_initialize();
    s_initialise();
    /*while(1)
      s_test(RIGHT);*/
    
    _delay_ms(5000.0);
    
    PORTB &= ~1;
    a_start();
}
