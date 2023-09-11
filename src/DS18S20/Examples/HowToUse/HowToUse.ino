#include <DS18S20.h>
#include<OneWire.h>


//The argument passed in the declaration is the OneWire pin. This library assumes there is only
//one device in the OneWire pin. So this would be the DS18S20 connection pin
DS18S20 termo(2);

void setup () {
  Serial.begin(9600);
}

void loop (){
   Serial.print("Celsius: ");
   Serial.println(termo.getTemp());
   Serial.print("Fahrenheit: ");
   Serial.println(termo.getTempF());
   Serial.print("Kelvin: ");
   Serial.println(termo.getTempK());
   delay(1000);
}

//termo.getTemp() returns a float which cointains the temperature in ºC
