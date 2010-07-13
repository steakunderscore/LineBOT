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

#include "sensor.h"
#define GREY_THRESH 128     // NOTE: these are currently might as well be random numbers and assume that complete blackness = 0, white = 256
#define WHITE_THRESH 192

/**
ADCsRA
ADEN 7 enables ADC
ADSC 6 = start conversion
ADFR 5 = free runnning (dont want)
ADIF 4 = interupt flag (1 if complete) (dont want)
ADIE 3 = interupt enabler, this along with SREG I-bit enable ADC Interupt (dont want)
00000111 = prescalar selections, initial try no scaling

ADMUX
will try 
REFS1 7 = 0 ,
REFS0 6 = 0 (Vref is AREF Internal Vref off)

ADLAR 5 = 1 (left adjust) (want)
bit4 - 0
MUX3 3 = input selections
MUX2 2 = input selections
MUX1 1 = input selections
MUX0 0 = input selections

MUX3->0 :
0000 = ADC0
0001 = ADC1
0010 = ADC2
0011 = ADC3
0100 = ADC4
0101 = ADC5
0110 = ADC6
0111 = ADC7 - check to see which pins using.'
*/
unsigned char s_check(unsigned char sensor) {
    uint8_t result= 0;
                            //check addresses are correct
    switch (sensor) {
        case RIGHT:  ADMUX =  BIT(ADLAR);              break; // RIGHT  = ADC0 = 0000  set for right sensor ADLAR = 1
        case CENTER: ADMUX = (BIT(ADLAR) | BIT(MUX0)); break; // CENTER = ADC1 = 0001
        case LEFT:   ADMUX = (BIT(ADLAR) | BIT(MUX1)); break; // LEFT   = ADC2 = 0010
    }
    
    ADCSRA |= BIT(ADSC); // starts ADC
    
    while(!(ADCSRA & BIT(ADIF))) {
        //waits for ADC CONVERSION
    }
    
    ADCSRA |= BIT(ADIF); // Writes a 1 to ADIF to clear it.
    
    if(ADCH < GREY_THRESH)
        result = S_BLACK;
    else if(ADCH < WHITE_THRESH)
        result = S_GREY;
    else
        result = S_WHITE;
    
    return result;
}

void s_initialise() {
    ADCSRA |= BIT(ADEN);
}
