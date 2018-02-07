#ifndef _FAN_H_
#define _FAN_H_

#include "Ventilator.h"

class Fan {
    public:
        Fan(uint16_t pin);
        void begin();
        void loop();
        /**
         * Set the fan speed from 0% (stopped) to 100% (max).
         */
        void setSpeed(int load);
    private:
        uint16_t _pin;
};

extern Fan fan;

#endif
