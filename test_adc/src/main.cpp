#include <Arduino.h>
#include <avr/io.h>
#include "adc_setup.h"

unsigned int sensorValue, adcChannel;
char dataBuffer[16];
int cmdInput;

void setup()
{
    sensorValue = 0;
    DDRB = 0x80;
    PORTB &= ~(0x80);
    adcChannel = 1;
    adcSetup(adcChannel);
    Serial.begin(38400);
    Serial.println("Program begins");
}

void loop()
{
    if (Serial.available())
    {
        cmdInput = Serial.read();
        if (cmdInput >= '0' && cmdInput <= '9')
        {
            adcChannel = cmdInput - '0';
        }
        else if (cmdInput >= 'A' && cmdInput <= 'F')
        {
            adcChannel = cmdInput - 'A' + 10;
        }
        else
        {
            adcChannel = 16;
        }

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

    if ((ADCSRA & 0x10) != 0)
    {
        sensorValue = ADC;
        ADCSRA |= 0x10;
        sprintf(dataBuffer, "Data: %4d\n", sensorValue);
        Serial.print(dataBuffer);
    }
}