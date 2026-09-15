#include <Arduino.h>
#include <Keyboard.h>
#include "dial_config.h"

const int WORKING_PIN = 9;
const int COUNTING_PIN = 10;

int working_state = 0;
int counter = 0;

bool lastCountingState = false;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 5;

bool is_dial_working() {
    return digitalRead(WORKING_PIN) == LOW;
}

bool is_dial_counting() {
    return digitalRead(COUNTING_PIN) == HIGH;
}

int pulses_to_digit(int pulseCount) {
    if (pulseCount < 1 || pulseCount > 10) return -1;
    return DIAL_MAP[pulseCount - 1];
}

const char* digit_to_string(int digit) {
    if (digit < 0 || digit > 9) return "";
    return DIGIT_STRINGS[digit];
}

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    pinMode(WORKING_PIN, INPUT_PULLUP);
    pinMode(COUNTING_PIN, INPUT_PULLUP);

    Keyboard.begin(KeyboardLayout_de_DE);
}

void loop() {
    while (is_dial_working()) {
        if (working_state == 0) {
            working_state = 1;
            counter = 0;
            lastCountingState = is_dial_counting();
        }

        bool currentCountingState = is_dial_counting();
        if (currentCountingState != lastCountingState) {
            unsigned long now = millis();
            if (now - lastDebounceTime > debounceDelay) {
                lastDebounceTime = now;
                if (currentCountingState) counter++;
                lastCountingState = currentCountingState;
            }
        }
    }

    if (working_state == 1) {
        int digit = pulses_to_digit(counter);
        const char* text = digit_to_string(digit);

        if (USE_DIGIT_STRINGS) {
            Serial.println(text);
            Keyboard.print(text);
        } else {
            Serial.println(digit);
            Keyboard.print(digit);
        }

        working_state = 0;
    }

    delay(20);
}
