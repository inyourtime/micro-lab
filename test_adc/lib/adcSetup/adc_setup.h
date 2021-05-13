#ifndef ADC_SETUP_H
#define ADC_SETUP_H

#include <Arduino.h>

void adcSetup(unsigned int ch);
int adcChangeChannel(unsigned int ch);

#endif