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

#include "constants.h"

#define S_WHITE ((unsigned char) 1)
#define S_BLACK ((unsigned char) 2)
#define S_GRAY  ((unsigned char) 3)

// Checks the given sensor and returns S_WHITE, S_BLACK or S_GRAY depending on
// the result.
unsigned char s_check(unsigned char sensor);
