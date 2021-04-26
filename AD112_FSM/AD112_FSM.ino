#define ledGrn 7
#define ledYel 6
#define ledRed 5
#define redBtn 0
#define yelBtn 1

uint8_t digit[16] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8,
                      0x80, 0x90, 0x88, 0x83, 0xA7, 0xA1, 0x86, 0x8E  
                    };

bool startBtn;
bool cancelBtn;
int state;

void setup() 
{
    DDRA |= 0xFF;
    DDRC &= ~((1 << redBtn) | (1 << yelBtn));
    DDRC |= 0xE0;

    PORTA |= 0xFF;
    PORTC |= 0xE0;
    PORTC &= ~(1 << ledGrn);
    state = 1;
}

void loop() 
{
    switch (state) {
        
        case 1:
            startBtn = PINC & 0x01;
            if (startBtn == 0) {
                for (int i = 5; i >= 0; i--) {
                    cancelBtn = PINC & 0x02;
                    if (cancelBtn == 0) {
                        break;
                    }
                    PORTA = digit[i];
                    delay(1000);
                }
                if (PORTA != digit[0]) {
                    PORTA |= 0xFF;
                    PORTC |= 0xE0;
                    PORTC &= ~(1 << ledGrn);
                    state = 1;
                } else {
                    state = 2;
                }
            } else {
                PORTA |= 0xFF;
                PORTC |= 0xE0;
                PORTC &= ~(1 << ledGrn);
                state = 1;
            }
            break;
        
        case 2:
            PORTC |= 0xE0;
            PORTC &= ~(1 << ledYel);
            delay(3000);
            state = 3;
            break;
        
        case 3:
            PORTC |= 0xE0;
            PORTC &= ~(1 << ledRed);
            for (int i = 9; i >= 0; i--) {
                PORTA = digit[i];
                delay(1000);
            }
            state = 1;
            break;
        
        default:
            PORTA |= 0xFF;
            PORTC |= 0xE0;
            PORTC &= ~(1 << ledGrn); 
            state = 1;    
    
    }
}
