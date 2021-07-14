
uint8_t digit[16] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
                      0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E  
                    };

int count = 0;
const int t1 = 100;

void setup() {
    // Led red yellow green
    DDRA |= 0x07;
    PORTA |= 0xFF;

    // 7 segments
    DDRC |= 0xFF;
    PORTC = digit[0];
//    PORTC |= 0xFF; 

    // 8 led module
    DDRK |= 0xFF;
    PORTK |= 0xFF;
}

void loop() {

//    task1();    // led traffic light module
    
//    task2();    // 7 segments module

    task3();

//    pattern1();

//    pattern2();

//    pattern3();
 
}

void task1() {
    for (int i = 0; i < 3; i++) {
        PORTA = ~(1 << i);
        delay(1000);
    }
}

void task2() {
    for (int i = 0; i < 16; i++) {
        PORTC = digit[i];
        delay(1000);
    }
}

void task3() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8-i; j++) {
            PORTK = ~(1 << j+i);
            for (int k = 0; k < i; k++) {
                PORTK &= ~(1 << k);
            }
            delay(t1);
        }
        for (int j = 6; j > i-1; j--) {
            PORTK = ~(1 << j);
            for (int k = 0; k < i; k++) {
                PORTK &= ~(1 << k);
            } 
            delay(t1);
        }
    }
    for (int i = 7; i >= 0; i--) {
        PORTK |= (1 << i);
        delay(t1);
    }
}

void pattern1() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (j > i) {
                PORTK = 0xFF;
                delay(t1);
                break; 
            }
            PORTK &= ~(1 << j);
            delay(t1);
            if (j == 7) {
                for (int k = 7; k >= 0; k--) {
                    PORTK |= (1 << k);
                    delay(t1);
                    if (k == 0) {
                        if (count == 15) count = -1;
                        PORTC = digit[count + 1];
                        count += 1;
                    }
                }
            }
        }
    }
}

void pattern2() {
    for (int i = 0; i < 8; i++) {
        PORTK = ~(1 << i);
        delay(200);
        if (i == 7) {
            if (count == 15) count = -1;
            PORTC = digit[count + 1];
            count += 1;
        }
    }
}

void pattern3() {
    for (int i = 0; i < 10; i++) {
        PORTK = ~((1 << i) | (1 << i-1) | (1 << i-2));
        delay(t1);
    }
}
