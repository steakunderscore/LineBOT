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
    m_initialize();
    s_initialise();

    _delay_ms(5000.0);

    a_start();
}
