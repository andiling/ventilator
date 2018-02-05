#include "Ventilator.h"

Fan::Fan(uint16_t pin) {
    this->_pin = pin;
}

void Fan::begin() {
    pinMode(this->_pin, OUTPUT);
}

void Fan::loop() {
    // Do nothing.
}

void Fan::setSpeed(int load) {
    int target = map(load, 0, 100, 0, PWMRANGE);
    analogWrite(this->_pin, target);
}

Fan fan = Fan(FAN_PIN);
