#include <Arduino.h>
#include <Keyboard.h>
#include "dial_config.h"
#include "dialer.h"

static Dialer dialer(9, 10);

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

    dialer.begin();
    Keyboard.begin(KEYBOARD_LAYOUT);
}

void loop() {
    if (dialer.update()) {
        int digit = pulses_to_digit(dialer.getCount());

        if (USE_DIGIT_STRINGS) {
            const char* text = digit_to_string(digit);
            Serial.println(text);
            Keyboard.print(text);
        } else {
            Serial.println(digit);
            Keyboard.print(digit);
        }
    }

    delay(20);
}
