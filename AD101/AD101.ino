
uint8_t digit[16] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
                      0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E  
                    };

void setup() {
    // Led red yellow green
    DDRA |= 0x07;
    PORTA |= 0xFF;

    // 7 segments
    DDRC |= 0xFF;
    PORTC |= 0xFF;

}

void loop() {

    // led traffic light
//    for (int i = 0; i < 3; i++) {
//        PORTA = ~(1 << i);
//        delay(1000);
//    }

    // 7 segments
    for (int i = 0; i < 16; i++) {
        PORTC = digit[i];
        delay(1000);
    }



}
