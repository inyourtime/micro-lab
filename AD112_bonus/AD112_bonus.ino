#define TRAFFIC_OFF ~(0x8)
#define TRAFFIC_GREEN ~(0x4)
#define TRAFFIC_YELLOW ~(0x2)
#define TRAFFIC_RED ~(0x1)
#define _7SEGMENTS_OFF 0xFF

#define SWITCH_RED 0xFE
#define SWITCH_YELLOW 0xFD
#define SWITCH_GREEN 0xFB
#define SWITCH_BLUE 0xF7
#define IR_SENSOR 0x7F

uint8_t digit[16] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
                      0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
                    };

int input;
int state;
int count;

void setup() {
  DDRC = 0xFF;    // 7 segments

  PORTK = 0xFF;
  DDRK = 0;

  DDRA |= 0x07;   // traffic light

  // initialize
  state = 1;
  count = 0;
  PORTC = _7SEGMENTS_OFF;
  PORTA = TRAFFIC_GREEN;
}

void loop() {
  switch (state) {

    case 1:
      input = PINK;
      if (input == SWITCH_RED) {
        state = 2;
        for (int i = 5; i >= 0; i--) {
          PORTC = digit[i];
          if (i == 0) break;
          delay(1000);
        }
        delay(300);
      } else if (input == SWITCH_YELLOW) {
        state = 4;
      } else {
        state = 1;
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

    case 4:
      input = PINK;
      PORTA = TRAFFIC_GREEN;
      PORTC = digit[count];
      if (input == IR_SENSOR) {
        if (count == 9) break;
        count += 1;
        PORTA = TRAFFIC_RED;
        delay(1000);
      } else if (input == SWITCH_RED) {
        state = 5;
      } else if (input == SWITCH_BLUE) {
        state = 1;
      }
      break;

    case 5:
      PORTC = digit[count];
      PORTA = TRAFFIC_YELLOW;
      input = PINK;
      if (input == SWITCH_YELLOW) {
        if (count == 0) break;
        count -= 1;
        delay(500);
      } else if (input == SWITCH_GREEN) {
        count = 0;
        delay(500);
      } else if (input == SWITCH_BLUE) {
        state = 4;
        delay(500);
      }
      break;

    default:
      state = 1;
      PORTC = _7SEGMENTS_OFF;
      PORTA = TRAFFIC_GREEN;

  }
}
