
const int varR = A1;
const int lightSensor = A2;
unsigned int varR_value, lightSensor_value;
char dataBuffer[30];
bool varBtnPress, lightBtnPress;

void setup()
{
    Serial.begin(38400);

    PORTA |= 0x3;
    DDRA &= 0xFC;
    varBtnPress = false;
    lightBtnPress = false;
    Serial.println("Program begin ... ");
}

void loop()
{
    if (varBtnPress == false)
    {
        if ((PINA & 0x1) == 0)
        {
            varBtnPress = true;
            delay(10);
            varR_value = analogRead(varR);
            sprintf(dataBuffer, "Value of varR: %4d\n", varR_value);
            Serial.print(dataBuffer);
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
            lightSensor_value = analogRead(lightSensor);
            sprintf(dataBuffer, "Value of light_sensor: %4d\n", lightSensor_value);
            Serial.print(dataBuffer);
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
}
