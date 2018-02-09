#include "Ventilator.h"

void handler() {
    fan.IRQCounter();
}

Fan::Fan(uint16_t fanPin, uint16_t rpmPin) {
    this->_fanPin = fanPin;
    this->_rpmPin = rpmPin;
    this->_targetRPM = 0;
    this->_currentLoad = 0;
    this->_interruptCounter = 0;
    this->_currentRPM = 0;
    this->_lastRPMCountEvent = 0;
    attachInterrupt(this->_rpmPin, handler, FALLING);
}

void Fan::begin() {
    pinMode(this->_fanPin, OUTPUT);
    pinMode(this->_rpmPin, INPUT);
}

void Fan::loop() {
    int target = map(this->_currentLoad, 0, 100, 0, 1023);
    analogWrite(this->_fanPin, target);
    checkRPMCounterInterval();
}

void Fan::setSpeed(int load) {
    // 100 = 935rpm  -> high
    // 15 = 615rpm   -> mid
    // 8 = 305rpm    -> low
    this->_currentLoad = load;
    // Spin up the fan. If the load goes from 0 to 8 the fan is not spinning up.
    analogWrite(this->_fanPin, 1023);
    delay(500);
}

void Fan::checkRPMCounterInterval() {
    if (this->_lastRPMCountEvent + RPM_COUNTER_INTERVAL <= millis()) {
        // We have 2 interrupts per rotation, so the formula is (interrupts / 2) * 60 000 / interval.
        this->_currentRPM = this->_interruptCounter * 30000 / RPM_COUNTER_INTERVAL;
        this->_interruptCounter = 0;
        this->_lastRPMCountEvent = millis();
    }
}

void Fan::IRQCounter() {
    this->_interruptCounter += 1;
    checkRPMCounterInterval();
}

int Fan::getRPM() {
    return this->_currentRPM;
}

Fan fan = Fan(FAN_PIN, FAN_RPM_PIN);
