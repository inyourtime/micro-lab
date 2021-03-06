#define TRAFFIC_OFF ~(0x8)
#define TRAFFIC_GREEN ~(0x4)
#define TRAFFIC_YELLOW ~(0x2)
#define TRAFFIC_RED ~(0x1)
#define _7SEGMENTS_OFF 0xFF

uint8_t digit[16] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
                      0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
                    };

int redBtn;
int state;

void setup() {
  DDRC = 0xFF;    // 7 segments

  PORTK |= 0x01;
  DDRK &= 0xFE;    // Button PORT K0

  DDRA |= 0x07;   // traffic light

  // initialize
  state = 1;
  PORTC = _7SEGMENTS_OFF;
  PORTA = TRAFFIC_GREEN;
}

void loop() {
  switch (state) {

    case 1:
      redBtn = PINK & 0x01;
      if (redBtn == 0) {
        state = 2;
        for (int i = 5; i >= 0; i--) {
          PORTC = digit[i];
          if (i == 0) break;
          delay(1000);
        }
        delay(300);
      } else {
        PORTC = _7SEGMENTS_OFF;
        PORTA = TRAFFIC_GREEN;
      }
      break;

    case 2:
      state = 3;
      PORTA = TRAFFIC_YELLOW;
      delay(3000);
      break;

    case 3:
      state = 1;
      PORTA = TRAFFIC_RED;
      for (int i = 9; i >= 0; i--) {
        PORTC = digit[i];
        if (i == 0) break;
        delay(1000);
      }
      delay(300);
      break;

    default:
      state = 1;
      PORTC = _7SEGMENTS_OFF;
      PORTA = TRAFFIC_GREEN;

  }
}
