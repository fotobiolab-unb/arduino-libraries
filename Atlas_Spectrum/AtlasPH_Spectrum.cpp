#include "AtlasPH_Spectrum.h"
#include "Arduino.h"
#include "SoftwareSerial.h"

//<<constructor>>
AtlasPH::AtlasPH(uint8_t RXPin, uint8_t TXPin):sSerial(RXPin,TXPin){
    _RXPin = RXPin;
    _TXPin = TXPin;
}
//<destructor>
AtlasPH::~AtlasPH () {}

void AtlasPH::initialize(){
    sSerial.begin(9600);

    delay(100);
    disableResponses();
//    disableLEDs();
    disableCont();
}

void AtlasPH::disableResponses(){
    sendCommand("RESPONSE,0");
}

void AtlasPH::disableCont(){
    sendCommand("C,0");
}

void AtlasPH::disableLEDs(){
    sendCommand("L,0");
}

void AtlasPH::sendCommand(String cmd){
//    SoftwareSerial sSerial(_RXPin, _TXPin);
    sSerial.print(cmd);
	sSerial.print("\r");
}

void AtlasPH::sendCommand(String cmd, float param){
//    SoftwareSerial sSerial(_RXPin, _TXPin);
    sSerial.print(cmd);
    sSerial.print(",");
    sSerial.print(param,2);
    sSerial.print("\r");
}

void AtlasPH::sendCommand(float param1, float param2){
 //   SoftwareSerial sSerial(_RXPin, _TXPin);
    sSerial.print(param1,2);
    sSerial.print(",");
    sSerial.print(param2,2);
    sSerial.print("\r");
}

float AtlasPH::getPHValue(){
    sendCommand("R");
    return read();
}

float AtlasPH::getPHValue(float param){
    sSerial.print("RT,");
    sSerial.print(param,2);
    sSerial.print("\r");
    return read();
}

float AtlasPH::read(){
    float value;
    String RawResponse;
    String Response;
 //   SoftwareSerial sSerial(_RXPin, _TXPin);

    delay(1000);

    while (sSerial.available()>0) {
        char inchar = (char)sSerial.read();
        RawResponse += inchar;
    }

	RawResponse += ","; // This comma will allow all three probes to be treated the same way
    Response = RawResponse.substring(0, RawResponse.indexOf(","));
    value = Response.toFloat();
	RawResponse = " ";
    return value;
}

void AtlasPH::calPH7(){
    sendCommand("cal,mid,7");
}

void AtlasPH::calPH4(){
    sendCommand("cal,low,4");
}

void AtlasPH::calPH10(){
    sendCommand("cal,high,10");
}