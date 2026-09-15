#ifndef KEYBOARD_WRAPPER_H
#define KEYBOARD_WRAPPER_H

#include "dial_config.h"

class KeyboardWrapper {
public:
    void begin() const {
        Keyboard.begin(KEYBOARD_LAYOUT);
    }

    int pulses_to_digit(int pulseCount) {
        if (pulseCount < 1 || pulseCount > 10) return -1;
        return DIAL_MAP[pulseCount - 1];
    }

    const char* digit_to_string(int digit) {
        if (digit < 0 || digit > 9) return "";
        return DIGIT_STRINGS[digit];
    }

    void write(const int pulses) {
        int digit = pulses_to_digit(pulses);
        if (USE_DIGIT_STRINGS) {
            const char* text = digit_to_string(digit);
            Keyboard.print(text);
        } else {
            Keyboard.print(digit);
        }
    }
};

#endif