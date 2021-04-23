bool stateStart = 0;

uint8_t digit[16] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8,
                      0x80, 0x90, 0x88, 0x83, 0xA7, 0xA1, 0x86, 0x8E  
                    };

void _crossTheRoad() 
{
    for (int i = 5; i >= 0; --i) {
        PORTA = digit[i];
        if (i == 0) {
           _preStop();
           _stop(); 
        }
        delay(1000);
    }
}

void _preStop() 
{
    PORTC |= ~ 0x7F;    // turn off LED green
    PORTC &= 0xBF;  // turn on LED yellow
    delay(3000); 
}

void _stop() 
{
    for (int i = 9; i >= 0; --i) {
        PORTC |= ~ 0xBF;    // turn off LED yellow
        PORTC &= 0xDF;  // turn on LED red
        PORTA = digit[i];
        delay(1000);
        if (i == 0) _reset();
    }
}

void _reset() 
{
    PORTA = 0xFF;   // turn off 7-segment
    PORTC &= 0x7F;  // turn on LED green
    PORTC |= 0x60;  // turn off LED yellow & red
}

void setup() 
{
    DDRA = 0xFF;    // set PORT A to digital output
    DDRC &= 0xFE;   // set PORT C0 to digital input
    DDRC |= 0xE0;   // set PORT C (PC7:5) to digital output 
                   
    PORTA = 0xFF;   // turn off 7-segment
    PORTC &= 0x7F;  // turn on LED green
    PORTC |= 0x60;  // turn off LED yellow & red
    
    Serial.begin(9600);
}

void loop() 
{
    stateStart = PINC & 0x01;   // read input from PC0
    Serial.println(stateStart);

    if (stateStart == 0) _crossTheRoad();
}
