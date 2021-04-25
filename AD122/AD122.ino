int ByteRx0, count;
char data_buffer[20];

void setup() {

    Serial.begin(38400);
    count = 0;

}

void loop() {

    ByteRx0 = 0;
    if (Serial.available()) {
        ByteRx0 = Serial.read();
        count++;
        Serial.print(count);
        Serial.print(": ");
        Serial.write(ByteRx0);
        Serial.print("\n");

        sprintf(data_buffer, "%d: %c", count, ByteRx0);
        Serial.println(data_buffer);
        sprintf(data_buffer, "%03d: %c", count, ByteRx0);
        Serial.println(data_buffer);
    }

}
