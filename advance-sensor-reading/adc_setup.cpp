#include <avr/io.h>
#include "adc_setup.h"

void adcSetup(unsigned int ch)
{
    ADCSRA = 0x97;
    ADCSRB = 0;
    ADMUX = 0x40;
    if (ch < 8)
    {
        ADMUX |= ch;
    }
    else 
    {
        ADCSRB |= 0x8; 
        ADMUX |= (ch & 0x7); 
    }
}

int adcChangeChannel(unsigned int ch)
{
    int output = 1;
    if (ch > 15)
    {
        output = 0;
    }
    else if (ch < 8)
    {
        ADMUX &= ~(0x1F);
        ADCSRB &= (0x47);
        ADMUX |= ch;
    }
    else
    {
        ADCSRB |= 0x8;
        ADMUX &= ~(0x1F);
        ADMUX |= (ch & 0x7);
    }
    return output;
}
