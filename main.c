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
void my_wait(volatile int i) {
    while(i--);
}

int main(void) {
    //s_initialise();
    m_initialize();

    m_reverse();
    my_wait(10000);
    m_turn(RIGHT);
    while(1);
}
