#include <Arduino.h>

#define LED_PIN 13
#define SPEED 1

void blink() {
    digitalWrite(LED_PIN, HIGH);
    delay(100 * SPEED);
    digitalWrite(LED_PIN, LOW);
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    blink();
    delay(200);
}
