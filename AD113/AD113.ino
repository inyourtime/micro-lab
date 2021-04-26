#define irSensor 0  // port C0
#define DV 7    // port D7
#define ledGrn 7    // port C7
#define ledYel 6    // port C6
#define ledRed 5    // port C5

const uint16_t myPassword = 123;
uint16_t enteredPassword;

uint8_t digit[4] = { 0xC0, 0xF9, 0xA4, 0xB0 };  // 7 segment 0,1,2,3 
int state;
                    
void setup() 
{
    Serial.begin(57600);
    
    /* ------------------set up port ------------------- */
    
    PORTK |= 0xFF;  // pull up port K
    DDRK &= 0x00;   // set port K to digital input of keypad
    
    PORTF |= (1 << DV);  // pull up port F7
    DDRF &= ~(1 << DV);  // set port F7 to digital input of DV keypad
    
    PORTC |= (1 << irSensor);  // pull up port C0
    DDRC &= ~(1 << irSensor);  // set port C0 to digital input of IR sensor
    
    PORTC |= 0x0E;  // pull up port C
    DDRC &= 0xF1;    // set up port H (PC3:1) to digital input of 3 Button ( red C3, yel C2, green C1 )
    
    DDRA |= 0xFF;   // set port A to digital output of 7 segment
    
    DDRC |= 0xE0;   // set port C (PC7:5) to digital output of traffic light
    
    /* ---------------------------------------------------*/
    
    /*  initialize  */

    PORTA |= 0xFF;
    PORTA = digit[3];

    PORTC |= 0xE0;
    PORTC &= ~(1 << ledGrn);
    state = 1;

    /* - - - - - - */
}

void loop() 
{
    switch (state) {

        case 1:
            while (PINC & 0x01) {}  // wait for IR sensor
            state = 2;
            break;
        
        case 2:
            if (PORTA == digit[0]) {       // if digit 0
                if (!(PINC & 0x02)) {      // if press EXIT button 
                    PORTA = digit[1];
                    PORTC |= 0xE0;
                    PORTC &= ~(1 << ledGrn);
                    state = 1; 
                }
                
                break;
                
            } else if (PORTA == digit[1]) {     // if digit 1
                if (!(PINC & 0x02)) {           // if press EXIT button
                    PORTA = digit[2];
                    state = 1;
                } else if (!(PINC & 0x08)) {    // if press START button
                    waitForStart();
                } else { break; }
                
                break;
                
            } else if (PORTA == digit[2]) {     // if digit 2
                if (!(PINC & 0x02)) {           // if press EXIT button
                    PORTA = digit[3];
                    state = 1;
                } else if (!(PINC & 0x08)) {    // if press START button
                    waitForStart(); 
                } else { break; }
                
                break;
                
            } else if (PORTA == digit[3]) {     // if digit 3
                if (!(PINC & 0x08)) {           // if press START button
                    waitForStart();
                } else { break; }
                
                break;
            }
        
        case 3:
            if (PORTA == digit[3]) {
                PORTA = digit[2];
                PORTC |= 0xE0;
                PORTC &= ~(1 << ledGrn);
                state = 1;
                break;
            } else if (PORTA == digit[2]) {
                PORTA = digit[1];
                PORTC |= 0xE0;
                PORTC &= ~(1 << ledGrn);
                state = 1;
                break;
            } else if (PORTA == digit[1]) {
                PORTA = digit[0];
                PORTC |= 0xE0;
                PORTC &= ~(1 << ledRed);
                state = 1;
                break;
            }
       
    }
}

void waitForStart() 
{
        PORTC |= 0xE0;
        PORTC &= ~(1 << ledYel);
        enteredPassword = readPassword();
        delay(10);
        while (enteredPassword != myPassword) {
            enteredPassword = readPassword();
        }
        state = 3;
}

uint16_t readPassword(void)
{
    uint8_t keypad[3];
    uint8_t password[3];
    uint16_t enteredPassword;
    uint8_t count = 0;
    bool doneFlag = false;
    uint8_t index;
    while (doneFlag == false) {
        if (PINF & 0x80) {
            keypad[count] = PINK;
            count++;
            Serial.write('.');
            while (PINF & 0x80) {}
        }
        if (count == 3) {
            doneFlag = true;
        }
    }

    for (index = 0; index < 3; index++) {
        switch (keypad[index]) {
            case 1:
                password[index] = 1; break;
            case 2:
                password[index] = 2; break;
            case 4:
                password[index] = 3; break;
            case 8:
                password[index] = 4; break;
            case 16:
                password[index] = 5; break;
            case 32:
                password[index] = 6; break;
            case 64:
                password[index] = 7; break;
            case 128:
                password[index] = 8; break;
        }
    }

    enteredPassword = (password[0] * 100) + (password[1] * 10) + password[2];
    while (PINC & 0x04) {}
    return(enteredPassword);
}
