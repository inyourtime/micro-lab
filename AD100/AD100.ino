uint8_t value1 = 0xFE;
uint8_t value = 0x01;
uint8_t digit[16] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
                      0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
                    };

const int delayTime = 200;
int count = 0;

void setup() {

    DDRC = 0xFF;
    DDRA = 0xFF;

    PORTC = digit[0];

}

void loop() {

    PORTA = value1;
    delay(delayTime);
    value = value << 1;
    value1 = ~value;

    if (value1 == 0x7F) {
        PORTA = value1;
        delay(delayTime);
        value1 = 0xFE;
        value = 0x01;
        PORTC = digit[count + 1];
        count++;

        if (count == 15) {
            count = -1;
        }
    }

}
