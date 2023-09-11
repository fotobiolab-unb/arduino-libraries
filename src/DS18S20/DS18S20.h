#ifndef DS18S20_H
#define DS18S20_H

#include "Arduino.h"
#include <OneWire.h>

class DS18S20 {
    public:
        DS18S20(int pin);
        ~DS18S20();
        float getTemp();
        float getTempF();
        float getTempK();
    private:
        OneWire ds;
};

#endif //DS18S20_end
