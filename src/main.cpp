#include <Arduino.h>
#include <Keyboard.h>
#include "keyboard_wrapper.h"
#include "dialer.h"

static Dialer dialer(9, 10);
static KeyboardWrapper keyboard;

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);

    dialer.begin();
    keyboard.begin();
}

void loop() {
    if (dialer.update()) {
        keyboard.write(dialer.getCount());
    }

    delay(20);
}
