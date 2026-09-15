#ifndef DIALER_H
#define DIALER_H

#include <Arduino.h>

class Dialer {
public:
    Dialer(const uint8_t workingPin, const uint8_t countingPin, unsigned long debounceMs = 5)
        : _workingPin(workingPin)
        , _countingPin(countingPin)
        , _debounceDelay(debounceMs)
    {}

    void begin() const {
        pinMode(_workingPin, INPUT_PULLUP);
        pinMode(_countingPin, INPUT_PULLUP);
    }

    bool update() {
        if (isWorking()) {
            if (!_wasWorking) {
                _counter = 0;
                _lastCountingState = isCounting();
                _wasWorking = true;
            }

            bool currentCountingState = isCounting();
            if (currentCountingState != _lastCountingState) {
                unsigned long now = millis();
                if (now - _lastDebounceTime > _debounceDelay) {
                    _lastDebounceTime = now;
                    if (currentCountingState) {
                        _counter++;
                    }
                    _lastCountingState = currentCountingState;
                }
            }
            return false;
        }

        if (_wasWorking) {
            _wasWorking = false;
            return true;
        }

        return false;
    }

    int getCount() const {
        return _counter;
    }

private:
    bool isWorking() const {
        return digitalRead(_workingPin) == LOW;
    }

    bool isCounting() const {
        return digitalRead(_countingPin) == HIGH;
    }

    uint8_t _workingPin;
    uint8_t _countingPin;
    unsigned long _debounceDelay;

    bool _wasWorking = false;
    bool _lastCountingState = false;
    unsigned long _lastDebounceTime = 0;
    int _counter = 0;
};

#endif // DIALER_H