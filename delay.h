/** @file   delay.h
    @author M. P. Hayes, UCECE
    @date   08 June 2002
    @brief  Delay routines for timing.
    @note   All files that use DELAY_US must be compiled with full optimisation.
*/
#ifndef DELAY_H
#define DELAY_H

#include "config.h"

/** This file provides a macro DELAY_US for microsecond delays
    and an inline function delay_ms for millisecond delays.
    The delays are implemented using busy wait loops.

    These routines are essentially flogged from the new version of
    avr/delay.h but generalised.  I have renamed _delay_us to
    delay_us_1, _delay_ms to delay_ms, added delay_us_2, and
    DELAY_US.  */


/** Private helper function for delay_us
    @param us delay in microseconds 

    @note The macro F_CPU is supposed to be defined to a
    constant defining the CPU clock frequency (in Hertz).

    @note The maximal possible delay is 768 us / F_CPU in MHz.  For a
    12 MHz clock the maximum delay is 64 us and for a 16 MHz clock the
    maximum delay is 48 us.  */
static __inline__ void
delay_us_1 (double us)
{
    uint8_t ticks;
    double tmp = ((F_CPU) / 3e6) * us;

    if (tmp < 1.0)
        ticks = 1;
    else if (tmp > 255)
        ticks = 0;    /* i.e., 256.  */
    else
        ticks = (uint8_t)tmp;
    _delay_loop_1 (ticks);
}


/** Private helper function for delay_us
    @param us delay in microseconds  */
static __inline__ void
delay_us_2 (double us)
{
    uint16_t ticks;
    double tmp = ((F_CPU) / 4e6) * us;

    if (tmp < 1.0)
        ticks = 1;
    else if (tmp > 65535)
        ticks = 0;    /* i.e., 65536.  */
    else
        ticks = (uint16_t)tmp;
    _delay_loop_2 (ticks);
}


#define DELAY1_LOOP_CYCLES 3
#define DELAY1_LOOPS_MAX 256
#define DELAY1_US_MAX (DELAY1_LOOPS_MAX * DELAY1_LOOP_CYCLES * 1e6 / (F_CPU))

#define DELAY2_LOOP_CYCLES 4
#define DELAY2_LOOPS_MAX 65536
#define DELAY2_US_MAX (DELAY2_LOOPS_MAX * DELAY2_LOOP_CYCLES * 1e6 / (F_CPU))


/** Delay a selected number of microseconds
    @param us number of microseconds to delay
    @note The maximal possible delay is 262.14 ms / F_CPU in MHz.
    @note This should be only used with a compile-time constant otherwise
    it will require floating point calls.  */
#define DELAY_US(us)                            \
do                                              \
{                                               \
    if ((us) > DELAY1_US_MAX)                   \
    {                                           \
        double __tmp2 = ((double)F_CPU * (us)) / (DELAY2_LOOP_CYCLES * 1e6);    \
        uint16_t __ticks2;                      \
                                                \
        if ((us) > DELAY2_US_MAX)               \
            __ticks2 = 0;                       \
        else                                    \
            __ticks2 = (uint16_t)__tmp2;                \
        _delay_loop_2 (__ticks2);               \
    }                                           \
    else                                        \
    {                                           \
        double __tmp1 = ((double)F_CPU * (us)) / (DELAY1_LOOP_CYCLES * 1e6);    \
        uint8_t __ticks1;                               \
                                                \
        if (__tmp1 < 1.0)                       \
            __ticks1 = 1;                       \
        else                                    \
            __ticks1 = (uint8_t)__tmp1;         \
        _delay_loop_1 (__ticks1);               \
    }                                           \
}                                               \
while (0)



/** Delay a selected number of milliseconds
    @param ms number of milliseconds to delay  */
static __inline__ void
delay_ms (uint8_t ms)
{
    /* FIXME:  "i" should only need to be a uint8_t
      Some bug has occured using a newer version of the avr-gcc that
      causes this routine to only delay 1ms if both "ms" and "i"
      are uint8_t. */
    uint16_t i;

    for (i = 0; i < ms; i++)
    {
        DELAY_US (1000);
    }
}


#endif /* DELAY_H  */
