
uint8_t digit[16] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
                      0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E  
                    };

int count = 0;

void setup() {
    // Led red yellow green
    DDRA |= 0x07;
    PORTA |= 0xFF;

    // 7 segments
    DDRC |= 0xFF;
//    PORTC = digit[0];
    PORTC |= 0xFF; 

    // 8 led module
    DDRF |= 0xFF;
    PORTF |= 0xFF;

}

void loop() {

    // led traffic light
    for (int i = 0; i < 3; i++) {
        PORTA = ~(1 << i);
        delay(1000);
    }

    // 7 segments
//    for (int i = 0; i < 16; i++) {
//        PORTC = digit[i];
//        delay(1000);
//    }

    // 8 led module
//    for (int i = 0; i < 8; i++) {
//        PORTF = ~(1 << i);
//        delay(200);
//        if (i == 7) {
//            if (count == 15) count = -1;
//            PORTC = digit[count + 1];
//            count += 1;
//        }
//    }

//    for (int i = 0; i < 8; i++) {
//        PORTF = ~(1 << i);
//        delay(200);
//        if (i == 7) {
//            for (int j = 6; j > 0; j--) {
//                PORTF = ~(1 << j);
//                delay(200);
//            }
//        }
//    }

//    for (int i = 0; i < 4; i++) {
//        PORTF = ~((1 << i) | (1 << 7-i));
//        delay(200);
//        if (i == 3) {
//            for (int j = 2; j > 0; j--) {
//                PORTF = ~((1 << j) | (1 << 7-j));
//                delay(200);
//            }
//        }
//    }


}
