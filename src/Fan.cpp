#include "Ventilator.h"

void handler() {
    fan.IRQCounter();
}

Fan::Fan(uint16_t fanPin, uint16_t rpmPin) {
    this->_fanPin = fanPin;
    this->_rpmPin = rpmPin;
    this->_targetRPM = 0;
    this->_currentLoad = 0;
    for (int i = 0; i < sizeof(this->_currentRPM) / sizeof(this->_currentRPM[0]); i++) {
        this->_currentRPM[i] = 0;
    }
    this->_lastCellSwitch = 0;
}

void Fan::begin() {
    pinMode(this->_fanPin, OUTPUT);
    pinMode(this->_rpmPin, INPUT);
}

void Fan::loop() {
    int target = map(this->_currentLoad, 0, 100, 0, 1023);
    analogWrite(this->_fanPin, target);
}

void Fan::setSpeed(int load) {
    // 100 = 935rpm  -> high
    // 15 = 615rpm   -> mid
    // 8 = 305rpm    -> low
    this->_currentLoad = load;

    if (load > 1) {
        this->_lastCellSwitch = millis();
        this->_currentRPM[0] = 0;
        attachInterrupt(this->_rpmPin, handler, FALLING);
    } else {
        detachInterrupt(this->_rpmPin);
        this->_currentRPM[1];
    }
}

void Fan::IRQCounter() {
    this->_currentRPM[0] += 1;
    if (this->_lastCellSwitch + RPM_COUNTER_INTERVAL <= millis()) {
        this->_currentRPM[1] = this->_currentRPM[0];
        this->_currentRPM[0] = 0;
        this->_lastCellSwitch = millis();
    }
}

int Fan::getRPM() {
    return this->_currentRPM[1] * 30000 / RPM_COUNTER_INTERVAL;
}

Fan fan = Fan(FAN_PIN, FAN_RPM_PIN);
