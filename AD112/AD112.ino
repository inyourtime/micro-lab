#define startBtn 8
#define ledYel 5
#define ledRed 6
#define ledGrn 7

int stateStart = 0;

uint8_t digit[16] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8,
                      0x80, 0x90, 0x88, 0x83, 0xA7, 0xA1, 0x86, 0x8E  
                    };

void _crossTheRoad() {
    
    for (int i = 5; i >= 0; --i) {
        PORTA = digit[i];
        if (i == 0) {
           _preStop();
           _stop(); 
        }
        delay(1000);
    }

    
}

void _preStop() {
    
    digitalWrite(ledGrn, HIGH);
    digitalWrite(ledYel, LOW);
    delay(3000); 

}

void _stop() {

    for (int i = 9; i >= 0; --i) {
        digitalWrite(ledYel, HIGH);
        digitalWrite(ledRed, LOW);
        PORTA = digit[i];
        delay(1000);

        if (i == 0) {
            _reset();
        }
    }
    
}

void _reset() {
    
    PORTA = 0xFF;
    digitalWrite(ledYel, HIGH);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGrn, LOW);
    
}

void setup() {

    DDRA = 0xFF;
    pinMode(startBtn, INPUT);
    pinMode(ledYel, OUTPUT);
    pinMode(ledRed, OUTPUT);
    pinMode(ledGrn, OUTPUT);

    PORTA = 0xFF;
    digitalWrite(ledYel, HIGH);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGrn, LOW);
    
    Serial.begin(9600);
    
}

void loop() {

    stateStart = digitalRead(startBtn);
    Serial.println(stateStart);

    if (stateStart == 0) {
        _crossTheRoad();
    }
    
}
