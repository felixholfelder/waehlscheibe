#ifndef DIAL_CONFIG_H
#define DIAL_CONFIG_H

#define KEYBOARD_LAYOUT KeyboardLayout_de_DE

const int DIAL_MAP[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
const bool USE_DIGIT_STRINGS = true;
const char* const DIGIT_STRINGS[10] = {
    "Harald ", // 0
    "a ", // 1
    "Zwei", // 2
    "Drei", // 3
    "Vier", // 4
    "Matz ", // 5
    "Sechs", // 6
    "Sieben", // 7
    "is ", // 8
    "Neun" // 9
};

#endif // DIAL_CONFIG_H