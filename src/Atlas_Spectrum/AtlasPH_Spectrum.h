/**

************  

*/


#ifndef AtlasPH_H
#define AtlasPH_H_H

#include "Arduino.h"
#include "SoftwareSerial.h"

class AtlasPH {
    public:
        AtlasPH(uint8_t RXPin, uint8_t TXPin);
        ~AtlasPH();
        void initialize();
        float getPHValue();
        float getPHValue(float param);
        void calPH7();
        void calPH4();
        void calPH10();

    private:
        byte _RXPin;
        byte _TXPin;

        SoftwareSerial sSerial;

        void disableResponses();
        void disableLEDs();
        void disableCont();

        void sendCommand(String cmd);
        void sendCommand(String cmd, float param);
        void sendCommand(float param1, float param2);
        float read();

};

#endif
