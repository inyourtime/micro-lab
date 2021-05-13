#ifndef _ADC_SETUP_H
#define _ADC_SETUP_H

#ifdef __cplusplus
extern "C"
{
#endif

    void adcSetup(unsigned int ch);
    int adcChangeChannel(unsigned int ch);


#ifdef __cplusplus
} // extern "C"
#endif

#endif
