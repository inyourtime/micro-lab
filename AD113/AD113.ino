#define irSensor 4  // port B4
#define DV 7    // port D7
#define ledGrn 7    // port B7
#define ledYel 6    // port B6
#define ledRed 5    // port B5
#define redBtn 6    // port H6
#define yelBtn 5    // port H5
#define grnBtn 4    // port H4

uint8_t digit[16] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8,
                      0x80, 0x90, 0x88, 0x83, 0xA7, 0xA1, 0x86, 0x8E  
                    };
                    
void setup() 
{
    PORTC |= 0xFF;  // pull up port C
    DDRC &= 0x00;   // set port C to digital input of keypad
    
    PORTD |= (1 << DV);  // pull up port D7
    DDRD &= ~(1 << DV);  // set port D7 to digital input of DV keypad
    
    PORTB |= (1 << irSensor);  // pull up port B4
    DDRB &= ~(1 << irSensor);  // set port B4 to digital input of IR sensor
    
    PORTH |= 0x70;  // pull up port H
    DDRH &= 0x8F    // set up port H (PH6:4) to digital input of 3 Button
    
    DDRA |= 0xFF;   // set port A to digital output of 7 segment
    
    DDRB |= 0xE0;   // set port B (PB7:5) to digital output of traffic light

    
}

void loop() 
{

}

uint16_t readKeypad(void)
{
    uint8_t keypad[3];
    uint8_t password[3];
    uint16_t myPassword;
    uint8_t count = 0;
    bool doneFlag = false;

    while (doneFlag == false) {
        if (PIND & 0x80) {
            keypad[count] = PINC;
            count++;
            Serial.write('.');
            while (PIND & 0x80) {}
        }
        if (count == 3) {
            doneFlag = true;
        }
    }

    for (uint8_t i = 0; i < 3; i++) {
        switch (keypad[i]) {
            case 1:
                password[i] = 1; break;
            case 2:
                password[i] = 2; break;
            case 4:
                password[i] = 3; break;
            case 8:
                password[i] = 4; break;
            case 16:
                password[i] = 5; break;
            case 32:
                password[i] = 6; break;
            case 64:
                password[i] = 7; break;
            case 128:
                password[i] = 8; break;
        }
    }

    myPassword = (password[0] * 100) + (password[1] * 10) + password[2];
    return(myPassword);
}
