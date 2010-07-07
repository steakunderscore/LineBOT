/* File:   config.h
   Author: M. P. Hayes, UCECE
   Date:   15 May 2007
   Descr:  Common configuration definitions.
*/
#ifndef CONFIG_H
#define CONFIG_H

/* Data typedefs.  */
#include <stdint.h>

typedef uint8_t bool;


/* Include target definitions.  */
#include "target.h"


/* Include system header files.  */
#if AVR
#include <util/delay.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#else
#include "avrdebug.h"
#endif


/* Define some useful macros.  */
#ifndef _BV
#define _BV(X) (1 << (X))
#endif

#ifndef BIT
#define BIT(X) _BV(X)
#endif

#define ARRAY_SIZE(ARRAY) (sizeof(ARRAY) / sizeof (ARRAY[0]))

#endif /* CONFIG_H  */


