#include "Ventilator.h"

Fan::Fan(uint16_t pin) {
    this->_pin = pin;
}

void Fan::begin() {
    pinMode(this->_pin, OUTPUT);
    // analogWriteFreq(65536);
}

void Fan::loop() {
    // Do nothing.
}

void Fan::setSpeed(int load) {
    int target = map(load, 0, 100, 0, PWMRANGE);
    Serial.print("Setting fan speed to ");
    Serial.println(target);
    analogWrite(this->_pin, target);
}

Fan fan = Fan(FAN_PIN);
