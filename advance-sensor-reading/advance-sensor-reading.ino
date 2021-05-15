#include "adc_setup.h"

#define varResister 1
#define lightSensor 2

unsigned int sensorValue;
unsigned int adcChannel;
char dataBuffer[30];
bool varBtnPress, lightBtnPress;

void adcStartConversion(unsigned int adcChannel)
{
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

void setup()
{
    PORTA |= 0x3;
    DDRA = 0xFC;
    sensorValue = 0;
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
            adcChannel = varResister;
            adcStartConversion(adcChannel);
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
            adcChannel = lightSensor;
            adcStartConversion(adcChannel);
        }
    }
    else
    {
        if ((PINA & 0x2) != 0)
        {
            lightBtnPress = false;
            delay(10);
        }
    }

    if ((ADCSRA & 0x10) != 0)
    {
        sensorValue = ADC;
        switch (adcChannel)
        {
        case varResister:
            ADCSRA |= 0x10;
            sprintf(dataBuffer, "Value of varR: %4d\n", sensorValue);
            Serial.print(dataBuffer);
            break;

        case lightSensor:
            ADCSRA |= 0x10;
            sprintf(dataBuffer, "Value of light_sensor: %4d\n", sensorValue);
            Serial.print(dataBuffer);
            break;

        default:
            break;
        }
    }
}
