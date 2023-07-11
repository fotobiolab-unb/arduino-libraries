
/**
  * @file       LVP.h
  * @brief      Library of the LVP serial communication
  * @author     Rodrigo Barbosa Nunes
  * @version    1.0
  * @date       2013
  *
  * The LVP library implements a extendable method of communication.
  * It gives the possibility to receive and send data via serial.
  * Methods and variables can be manipulated using the LVP too.
  *
  */

#ifndef LVP_H
#define LVP_H

#include "Arduino.h"

//Defines the enum for each variable type

///Enumaration for variable type integer
const byte intVar=0;

///Enumaration for variable type float
const byte floatVar=1;

///Enumaration for variable type double
const byte doubleVar=2;

///Enumaration for variable type byte
const byte byteVar=3;

///Enumaration for variable type long
const byte varLong=4;

///Enumaration for variable type unsigned
const byte unsignedvarLong=5;

///Enumaration for variable type word
const byte wordVar=6;

///Enumaration for variable type short
const byte shortVar=7;


///Class that models the LVP communication.
class LVP
{
  public:
    /**
      * @brief  Unique constructor of the class
      * @param  numData Number of datas (parameters and results)
      * @param  numFunctions Number of functions
      * @param  baudRate Baud rate used in the serial
      *
      */
    LVP(byte numData, byte numFunctions, long baudRate);

    ///Initialization of the LVP class
    void initialize();

    //functio

    /**
      * @brief  Add a function to the LVP
      * @param  label Label of the function
      * @param  functionPointer Address of the function
      *
      * A function that is added can be used during the execution.
      * Note that only function that have void return and parameter can be added.
      *
      */
    void addFunction(String label, void (*functionPointer)(void));

    //short

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the short parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,short*pointer);

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the short parameter
      * @param  defaultValue Default short value of the parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,short*pointer,short defaultValue);

    /**
      * @brief  Add a result to the LVP
      * @param  label Label of the result
      * @param  pointer Address of the short result
      *
      * A result that is added can be used in the "get" functions of the LVP.
      * Results are parameters that can't be changed
      *
      */
    void addResult(String label,short*pointer);

    /**
      * @brief  Sets a default value to a parameter.
      * @param  label Label of the parameter
      * @param  defaultValue Default short value of the parameter
      *
      */
    void setDefaultValue(String label, short defaultValue);

    //int

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the int parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,int*pointer);

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the itn parameter
      * @param  defaultValue Default int value of the parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,int*pointer,int defaultValue);

    /**
      * @brief  Add a result to the LVP
      * @param  label Label of the result
      * @param  pointer Address of the int result
      *
      * A result that is added can be used in the "get" functions of the LVP.
      * Results are parameters that can't be changed
      *
      */
    void addResult(String label,int*pointer);

    /**
      * @brief  Sets a default value to a parameter.
      * @param  label Label of the parameter
      * @param  defaultValue Default int value of the parameter
      *
      */
    void setDefaultValue(String label, int defaultValue);

    //word

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the word parameter
      * @param  defaultValue Default word value of the parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,word* pointer);

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the word parameter
      * @param  defaultValue Default word value of the parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,word*pointer,word defaultValue);

    /**
      * @brief  Add a result to the LVP
      * @param  label Label of the result
      * @param  pointer Address of the word result
      *
      * A result that is added can be used in the "get" functions of the LVP.
      * Results are parameters that can't be changed
      *
      */
    void addResult(String label,word*pointer);

    /**
      * @brief  Sets a default value to a parameter.
      * @param  label Label of the parameter
      * @param  defaultValue Default word value of the parameter
      *
      */
    void setDefaultValue(String label, word defaultValue);

    //float

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the float parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,float*pointer);

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the float parameter
      * @param  defaultValue Default float value of the parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,float*pointer,float defaultValue);

    /**
      * @brief  Add a result to the LVP
      * @param  label Label of the result
      * @param  pointer Address of the float result
      *
      * A result that is added can be used in the "get" functions of the LVP.
      * Results are parameters that can't be changed
      *
      */
    void addResult(String label,float*pointer);

    /**
      * @brief  Sets a default value to a parameter.
      * @param  label Label of the parameter
      * @param  defaultValue Default float value of the parameter
      *
      */
    void setDefaultValue(String label, float defaultValue);

    //double

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the double parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,double*pointer);

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the double parameter
      * @param  defaultValue Default double value of the parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,double*pointer,double defaultValue);

    /**
      * @brief  Add a result to the LVP
      * @param  label Label of the result
      * @param  pointer Address of the double result
      *
      * A result that is added can be used in the "get" functions of the LVP.
      * Results are parameters that can't be changed
      *
      */
    void addResult(String label,double*pointer);

    /**
      * @brief  Sets a default value to a parameter.
      * @param  label Label of the parameter
      * @param  defaultValue Default double value of the parameter
      *
      */
    void setDefaultValue(String label, double defaultValue);

    //byte

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the byte parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,byte*pointer);

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the byte parameter
      * @param  defaultValue Default byte value of the parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,byte*pointer,byte defaultValue);

    /**
      * @brief  Add a result to the LVP
      * @param  label Label of the result
      * @param  pointer Address of the byte result
      *
      * A result that is added can be used in the "get" functions of the LVP.
      * Results are parameters that can't be changed
      *
      */
    void addResult(String label,byte*pointer);

    /**
      * @brief  Sets a default value to a parameter.
      * @param  label Label of the parameter
      * @param  defaultValue Default byte value of the parameter
      *
      */
    void setDefaultValue(String label, byte defaultValue);

    //long

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the long parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,long*pointer);

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the long parameter
      * @param  defaultValue Default long value of the parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,long*pointer,long defaultValue);

    /**
      * @brief  Add a result to the LVP
      * @param  label Label of the result
      * @param  pointer Address of the long result
      *
      * A result that is added can be used in the "get" functions of the LVP.
      * Results are parameters that can't be changed
      *
      */
    void addResult(String label,long*pointer);

    /**
      * @brief  Sets a default value to a parameter.
      * @param  label Label of the parameter
      * @param  defaultValue Default long value of the parameter
      *
      */
    void setDefaultValue(String label, long defaultValue);

    //unsigned long

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the unsigned long parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,unsigned long*pointer);

    /**
      * @brief  Add a parameter to the LVP
      * @param  label Label of the parameter
      * @param  pointer Address of the unsigned long parameter
      * @param  defaultValue Default unsigned long value of the parameter
      *
      * A parameter that is added can be used in the "set" and "get" functions of the LVP.
      *
      */
    void addParameter(String label,unsigned long*pointer,unsigned long defaultValue);

    /**
      * @brief  Add a result to the LVP
      * @param  label Label of the result
      * @param  pointer Address of the unsigned long result
      *
      * A result that is added can be used in the "get" functions of the LVP.
      * Results are parameters that can't be changed
      *
      */
    void addResult(String label,unsigned long*pointer);

    /**
      * @brief  Sets a default value to a parameter.
      * @param  label Label of the parameter
      * @param  defaultValue Default unsigned long value of the parameter
      *
      */
    void setDefaultValue(String label, unsigned long defaultValue);

    ///Get a new command on the serial
    void getNewCommand();

    ///Indicates if the connection is open
    boolean isConnected();

    /**
      * @brief  Get the state of the connection
      * @return State of the connection
      *
      */
    String getState();

  private:

    ///Command adquired
    String command;

    ///Arguments adquired
    String arguments;

    ///Messages adquired
    String messages;

    ///Warnings adquired
    String warnings;

    ///String of data adquired
    String dataString;

    ///Baud rate of the connection
    long _baudRate;

    ///Number of active editable datas
    byte _numData;

    ///Number of active functions
    byte _numFunctions;

    ///Indicates if the connection is setted as "auto"
    boolean _autoConnection;

    ///Indicates if the connection is setted as "manual"
    boolean _manualConnection;

    ///Indicates if the connection is setted as "quiet"
    boolean _quietConnection;

    ///Current index of editable datas being used
    byte _currentIndex;

    ///Current index of functions being used
    byte _currentFIndex;

    /**
      * @brief  Struct of the datas
      *
      *
      */
    struct dataStruct {
      String label;
      union PointerType {
        byte* Byte;
        int* Int;
        word* Word;
        long* Long;
        unsigned long* UnsignedLong;
        short* Short;
        float* Float;
        double* Double;
      } pointer;

      union DefaultValue {
        byte Byte;
        int Int;
        word Word;
        long Long;
        unsigned long UnsignedLong;
        short Short;
        float Float;
        double Double;
      } defaultValue;
      byte varType;
      boolean isParameter;
      boolean hasDefault;
    } *data;

    struct functionStruct {

      String label;
      void (*pointer) (void);
    } *function;

    void selectCommand();
    void sendAll();
    void establishConnection(byte option);
    void endConnection();
    void test();
    int searchDataFor(String label);
    int searchFunctionFor(String label);
    void sendStrings();
    void processArguments(byte option);
    boolean isNumber(char c);
    String getNextSubstring();
    String valueToString(byte value);
    String valueToString(word value);
    String valueToString(short value);
    String valueToString(long value);
    String valueToString(unsigned long value);
    String valueToString(double value);
    String valueToString(int value);
    String valueToString(float value);
    void resetToDefaultValues();
    String dataValueToString(dataStruct arg);
};

#endif // LVP_H
