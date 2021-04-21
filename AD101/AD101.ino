void setup() {

    DDRA = 0xFF;
    PORTA = 0xFF;

}

void loop() {

    for (int i = 0; i < 8; i++) {
        PORTA = ~ (1 << i);
        delay(1000);
    }

}
