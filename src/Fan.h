#ifndef _FAN_H_
#define _FAN_H_

#include "Ventilator.h"

#define RPM_COUNTER_INTERVAL 6000

class Fan {
    public:
        Fan(uint16_t fanPin, uint16_t rpmPin);
        void begin();
        void loop();
        void IRQCounter();
        /**
         * Set the fan speed from 0% (stopped) to 100% (max).
         */
        void setSpeed(int load);

        int getRPM();
    private:
        uint16_t _fanPin;
        uint16_t _rpmPin;
        int _targetRPM;
        int _currentLoad;
        volatile unsigned long _lastCellSwitch;
        // Keeps the last 6 second RPMs in [1] and the currently counting RPMs in [0]
        volatile int _currentRPM[2];

};

extern Fan fan;

#endif
