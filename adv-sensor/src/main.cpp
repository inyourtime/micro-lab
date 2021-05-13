#include <Arduino.h>
#include <avr/io.h>
#include "adc_setup.h"

unsigned int sensorValue;
unsigned int adcChannel;
char dataBuffer[30];
bool varBtnPress, lightBtnPress;

void setup()
{
    PORTA |= 0x3;
    DDRA = 0xFC;
    sensorValue= 0;
    varBtnPress = lightBtnPress = false;
    adcChannel = 0;
    adcSetup(adcChannel);

    Serial.begin(38400); // start Serial port
    Serial.println("Program begins");
}

void loop()
{
    if (varBtnPress == false)
    {
        if ((PINA & 0x1) == 0)
        {
            varBtnPress = true;
            delay(10);
            adcChannel = 1;
            if (adcChangeChannel(adcChannel))
            {
                if ((ADCSRA & 0x40) == 0)
                {
                    ADCSRA |= 0x40;
                }
                else
                {
                    Serial.println("Err: ADC change channel");
                }
            }
        }
    }
    else
    {
        if ((PINA & 0x1) != 0)
        {
            varBtnPress = false;
            delay(10);
        }
    }

    if (lightBtnPress == false)
    {
        if ((PINA & 0x2) == 0)
        {
            lightBtnPress = true;
            delay(10);
            adcChannel = 2;
            if (adcChangeChannel(adcChannel))
            {
                if ((ADCSRA & 0x40) == 0)
                {
                    ADCSRA |= 0x40;
                }
                else
                {
                    Serial.println("Err: ADC change channel");
                }
            }
        }
    }
    else
    {
        lightBtnPress = false;
        delay(10);
    }

    if ((ADCSRA & 0x10) != 0)
    {
        sensorValue = ADC;
        switch (adcChannel)
        {
        case 1:
            ADCSRA |= 0x10;
            sprintf(dataBuffer, "Value of varR: %4d\n", sensorValue);
            Serial.print(dataBuffer);
            break;
        
        case 2:
            ADCSRA |= 0x10;
            sprintf(dataBuffer, "Value of light_sensor: %4d\n", sensorValue);
            Serial.print(dataBuffer);
            break;
        
        default:
            break;
        }
    }
}