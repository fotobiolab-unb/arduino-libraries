 #include "LVP.h"
#include "Arduino.h"

//Defines of establishConnection() options
const byte manual_option=0;                       //Used to establish a manual connection
const byte auto_option=1;                      //Used to establish an automatic connection
const byte quiet_option=2;

//Defines of processArguments() options
const byte get_option=0;
const byte set_option=1;

LVP::LVP(byte numData, byte numFunctions, long baudRate) {
  _numData=numData;
  _numFunctions=numFunctions;
  _baudRate=baudRate;
}

void LVP::initialize() {

  command="";
  arguments="";
  messages="";
  dataString="";
  warnings="";
  Serial.begin(_baudRate);
  data = (dataStruct*) calloc(_numData,sizeof(dataStruct));
  function = (functionStruct*) calloc(_numFunctions,sizeof(functionStruct));
  _currentIndex=0;
  _currentFIndex=0;
}


void LVP::addFunction(String label, void (*functionPointer)(void)){

  if(_currentFIndex<_numFunctions){

    function[_currentFIndex].label=label;
    function[_currentFIndex].pointer=functionPointer;
    _currentFIndex++;
  }

}
void LVP::addParameter(String label,byte*pointer){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Byte=pointer;
    data[_currentIndex].varType=byteVar;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}

void LVP::addParameter(String label,byte*pointer,byte defaultValue){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Byte=pointer;
    data[_currentIndex].defaultValue.Byte=defaultValue;
    data[_currentIndex].varType=byteVar;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=true;

    _currentIndex++;
  }
}

void LVP::addResult(String label,byte*pointer){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Byte=pointer;
    data[_currentIndex].varType=byteVar;
    data[_currentIndex].isParameter=false;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}

void LVP::setDefaultValue(String label,byte defaultValue){

  int index=searchDataFor(label);
  if (index>=0&&data[index].isParameter){

    data[index].hasDefault=true;

    switch(data[index].varType){

      case byteVar:
        data[index].defaultValue.Byte=(byte) defaultValue;
        break;
      case intVar:
        data[index].defaultValue.Int=(int) defaultValue;
        break;
      case wordVar:
        data[index].defaultValue.Word=(word) defaultValue;
        break;
      case varLong:
        data[index].defaultValue.Long=(long) defaultValue;
        break;
      case unsignedvarLong:
        data[index].defaultValue.UnsignedLong=(unsigned long)defaultValue;
        break;
      case shortVar:
        data[index].defaultValue.Short=(short)defaultValue;
        break;
      case floatVar:
        data[index].defaultValue.Float=(float) defaultValue;
        break;
      case doubleVar:
        data[index].defaultValue.Double=(double) defaultValue;
        break;
    }
  }
}

String LVP::valueToString (byte value){

  String str= String(value,DEC);

  return str;
}

void LVP::addParameter(String label,double*pointer){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Double=pointer;
    data[_currentIndex].varType=doubleVar;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}
void LVP::addParameter(String label,double*pointer,double defaultValue){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Double=pointer;
    data[_currentIndex].defaultValue.Double=defaultValue;
    data[_currentIndex].varType=doubleVar;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=true;

    _currentIndex++;
  }
}
void LVP::addResult(String label,double*pointer){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Double=pointer;
    data[_currentIndex].varType=doubleVar;
    data[_currentIndex].isParameter=false;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}
void LVP::setDefaultValue(String label,double defaultValue){

  int index=searchDataFor(label);
  if (index>=0&&data[index].isParameter){

    data[index].hasDefault=true;

    switch(data[index].varType){

      case byteVar:
        data[index].defaultValue.Byte=(byte) defaultValue;
        break;
      case intVar:
        data[index].defaultValue.Int=(int) defaultValue;
        break;
      case wordVar:
        data[index].defaultValue.Word=(word) defaultValue;
        break;
      case varLong:
        data[index].defaultValue.Long=(long) defaultValue;
        break;
      case unsignedvarLong:
        data[index].defaultValue.UnsignedLong=(unsigned long)defaultValue;
        break;
      case shortVar:
        data[index].defaultValue.Short=(short)defaultValue;
        break;
      case floatVar:
        data[index].defaultValue.Float=(float) defaultValue;
        break;
      case doubleVar:
        data[index].defaultValue.Double=(double) defaultValue;
        break;
    }
  }
}

String LVP::valueToString (double value){

  char char_array[15];                         //Used to temporarily store the converted float. As described in clarification #7, 14 chars are more than enough

  dtostrf(value,1,6,char_array);                 //dtostrf( doubleVariable , minimumLengthOfDoubleVariable , NumberOfDigitsAfterPoint , ArrayWhereItWillBeStored )

  String str= String(char_array);

  return str;
}

void LVP::addParameter(String label,float*pointer){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Float=pointer;
    data[_currentIndex].varType=floatVar;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}
void LVP::addParameter(String label,float*pointer,float defaultValue){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Float=pointer;
    data[_currentIndex].defaultValue.Float=defaultValue;
    data[_currentIndex].varType=floatVar;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=true;

    _currentIndex++;
  }
}
void LVP::addResult(String label,float*pointer){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Float=pointer;
    data[_currentIndex].varType=floatVar;
    data[_currentIndex].isParameter=false;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}
void LVP::setDefaultValue(String label,float defaultValue){

  int index=searchDataFor(label);
  if (index>=0&&data[index].isParameter){

    data[index].hasDefault=true;

    switch(data[index].varType){

      case byteVar:
        data[index].defaultValue.Byte=(byte) defaultValue;
        break;
      case intVar:
        data[index].defaultValue.Int=(int) defaultValue;
        break;
      case wordVar:
        data[index].defaultValue.Word=(word) defaultValue;
        break;
      case varLong:
        data[index].defaultValue.Long=(long) defaultValue;
        break;
      case unsignedvarLong:
        data[index].defaultValue.UnsignedLong=(unsigned long)defaultValue;
        break;
      case shortVar:
        data[index].defaultValue.Short=(short)defaultValue;
        break;
      case floatVar:
        data[index].defaultValue.Float=(float) defaultValue;
        break;
      case doubleVar:
        data[index].defaultValue.Double=(double) defaultValue;
        break;
    }
  }
}

String LVP::valueToString (float value){

  char char_array[15];                         //Used to temporarily store the converted float. As described in clarification #7, 14 chars are more than enough

  dtostrf(value,1,6,char_array);                 //dtostrf( floatVariable , minimumLengthOfFloatVariable , NumberOfDigitsAfterPoint , ArrayWhereItWillBeStored )

  String str= String(char_array);

  return str;
}

void LVP::addParameter(String label,int*pointer){

  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Int=pointer;
    data[_currentIndex].varType=intVar;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}

void LVP::addParameter(String label,int*pointer,int defaultValue){

  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Int=pointer;
    data[_currentIndex].defaultValue.Int=defaultValue;
    data[_currentIndex].varType=intVar;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=true;

    _currentIndex++;
  }
}

void LVP::addResult(String label,int*pointer){

  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Int=pointer;
    data[_currentIndex].varType=intVar;
    data[_currentIndex].isParameter=false;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}

void LVP::setDefaultValue(String label,int defaultValue){

  int index=searchDataFor(label);
  if (index>=0&&data[index].isParameter){

    data[index].hasDefault=true;

    switch(data[index].varType){

      case byteVar:
        data[index].defaultValue.Byte=(byte)defaultValue;
        break;
      case intVar:
        data[index].defaultValue.Int=(int) defaultValue;
        break;
      case wordVar:
        data[index].defaultValue.Word=(word) defaultValue;
        break;
      case varLong:
        data[index].defaultValue.Long=(long) defaultValue;
        break;
      case unsignedvarLong:
        data[index].defaultValue.UnsignedLong=(unsigned long)defaultValue;
        break;
      case shortVar:
        data[index].defaultValue.Short=(short)defaultValue;
        break;
      case floatVar:
        data[index].defaultValue.Float=(float) defaultValue;
        break;
      case doubleVar:
        data[index].defaultValue.Double=(double) defaultValue;
        break;
    }
  }
}

String LVP::valueToString (int value){

  String str= String(value,DEC);

  return str;
}

void LVP::addParameter(String label,long*pointer){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Long=pointer;
    data[_currentIndex].varType=varLong;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}
void LVP::addParameter(String label,long*pointer,long defaultValue){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Long=pointer;
    data[_currentIndex].defaultValue.Long=defaultValue;
    data[_currentIndex].varType=varLong;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=true;

    _currentIndex++;
  }
}
void LVP::addResult(String label,long*pointer){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Long=pointer;
    data[_currentIndex].varType=varLong;
    data[_currentIndex].isParameter=false;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}
void LVP::setDefaultValue(String label,long defaultValue){

  int index=searchDataFor(label);
  if (index>=0&&data[index].isParameter){

    data[index].hasDefault=true;

    switch(data[index].varType){

      case byteVar:
        data[index].defaultValue.Byte=(byte) defaultValue;
        break;
      case intVar:
        data[index].defaultValue.Int=(int) defaultValue;
        break;
      case wordVar:
        data[index].defaultValue.Word=(word) defaultValue;
        break;
      case varLong:
        data[index].defaultValue.Long=(long) defaultValue;
        break;
      case unsignedvarLong:
        data[index].defaultValue.UnsignedLong=(unsigned long)defaultValue;
        break;
      case shortVar:
        data[index].defaultValue.Short=(short)defaultValue;
        break;
      case floatVar:
        data[index].defaultValue.Float=(float) defaultValue;
        break;
      case doubleVar:
        data[index].defaultValue.Double=(double) defaultValue;
        break;
    }
  }
}

String LVP::valueToString (long value){

  String str= String(value,DEC);

  return str;
}

void LVP::addParameter(String label,short*pointer){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Short=pointer;
    data[_currentIndex].varType=shortVar;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}
void LVP::addParameter(String label,short*pointer,short defaultValue){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Short=pointer;
    data[_currentIndex].defaultValue.Short=defaultValue;
    data[_currentIndex].varType=shortVar;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=true;

    _currentIndex++;
  }
}
void LVP::addResult(String label,short*pointer){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Short=pointer;
    data[_currentIndex].varType=shortVar;
    data[_currentIndex].isParameter=false;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}
void LVP::setDefaultValue(String label,short defaultValue){

  int index=searchDataFor(label);
  if (index>=0&&data[index].isParameter){

    data[index].hasDefault=true;

    switch(data[index].varType){

      case byteVar:
        data[index].defaultValue.Byte=(byte) defaultValue;
        break;
      case intVar:
        data[index].defaultValue.Int=(int) defaultValue;
        break;
      case wordVar:
        data[index].defaultValue.Word=(word) defaultValue;
        break;
      case varLong:
        data[index].defaultValue.Long=(long) defaultValue;
        break;
      case unsignedvarLong:
        data[index].defaultValue.UnsignedLong=(unsigned long)defaultValue;
        break;
      case shortVar:
        data[index].defaultValue.Short=(short)defaultValue;
        break;
      case floatVar:
        data[index].defaultValue.Float=(float) defaultValue;
        break;
      case doubleVar:
        data[index].defaultValue.Double=(double) defaultValue;
        break;
    }
  }
}

String LVP::valueToString (short value){

  String str= String(value,DEC);

  return str;
}

void LVP::addParameter(String label,unsigned long*pointer){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.UnsignedLong=pointer;
    data[_currentIndex].varType=unsignedvarLong;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}
void LVP::addParameter(String label,unsigned long*pointer,unsigned long defaultValue){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.UnsignedLong=pointer;
    data[_currentIndex].defaultValue.UnsignedLong=defaultValue;
    data[_currentIndex].varType=unsignedvarLong;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=true;

    _currentIndex++;
  }
}
void LVP::addResult(String label,unsigned long*pointer){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.UnsignedLong=pointer;
    data[_currentIndex].varType=unsignedvarLong;
    data[_currentIndex].isParameter=false;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}
void LVP::setDefaultValue(String label,unsigned long defaultValue){

  int index=searchDataFor(label);
  if (index>=0&&data[index].isParameter){

    data[index].hasDefault=true;

    switch(data[index].varType){

      case byteVar:
        data[index].defaultValue.Byte=(byte) defaultValue;
        break;
      case intVar:
        data[index].defaultValue.Int=(int) defaultValue;
        break;
      case wordVar:
        data[index].defaultValue.Word=(word) defaultValue;
        break;
      case varLong:
        data[index].defaultValue.Long=(long) defaultValue;
        break;
      case unsignedvarLong:
        data[index].defaultValue.UnsignedLong=(unsigned long)defaultValue;
        break;
      case shortVar:
        data[index].defaultValue.Short=(short)defaultValue;
        break;
      case floatVar:
        data[index].defaultValue.Float=(float) defaultValue;
        break;
      case doubleVar:
        data[index].defaultValue.Double=(double) defaultValue;
        break;
    }
  }
}

String LVP::valueToString (unsigned long value){

  String str= String(value,DEC);

  return str;
}

void LVP::addParameter(String label,word*pointer){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Word=pointer;
    data[_currentIndex].varType=wordVar;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}

void LVP::addParameter(String label,word*pointer,word defaultValue){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Word=pointer;
    data[_currentIndex].defaultValue.Word=defaultValue;
    data[_currentIndex].varType=wordVar;
    data[_currentIndex].isParameter=true;
    data[_currentIndex].hasDefault=true;

    _currentIndex++;
  }
}

void LVP::addResult(String label,word*pointer){
  if (_currentIndex<_numData){
    data[_currentIndex].label=label;
    data[_currentIndex].pointer.Word=pointer;
    data[_currentIndex].varType=wordVar;
    data[_currentIndex].isParameter=false;
    data[_currentIndex].hasDefault=false;

    _currentIndex++;
  }
}

void LVP::setDefaultValue(String label,word defaultValue){

  int index=searchDataFor(label);
  if (index>=0&&data[index].isParameter){

    data[index].hasDefault=true;

    switch(data[index].varType){

      case byteVar:
        data[index].defaultValue.Byte=(byte) defaultValue;
        break;
      case intVar:
        data[index].defaultValue.Int=(int) defaultValue;
        break;
      case wordVar:
        data[index].defaultValue.Word=(word) defaultValue;
        break;
      case varLong:
        data[index].defaultValue.Long=(long) defaultValue;
        break;
      case unsignedvarLong:
        data[index].defaultValue.UnsignedLong=(unsigned long)defaultValue;
        break;
      case shortVar:
        data[index].defaultValue.Short=(short)defaultValue;
        break;
      case floatVar:
        data[index].defaultValue.Float=(float) defaultValue;
        break;
      case doubleVar:
        data[index].defaultValue.Double=(double) defaultValue;
        break;
    }
  }
}

String LVP::valueToString (word value){

  String str= String(value,DEC);

  return str;
}

void LVP::processArguments(byte option){

  arguments=arguments.substring(1);
  //Serial.println("'"+arguments+"'");

  String currentString;

  do {

    currentString = getNextSubstring();
    int index=searchDataFor(currentString);
    if (index<0){

      warnings+="Label '"+currentString+"' not found.,";

      //Remove a value, if it exists, typed after a nonexistent label
      if(isNumber(arguments.charAt(0))) {

        getNextSubstring();
        continue;
      }
    }
    else if (option==set_option){

      //Ignores the current label, if a value wasn't typed after it
      if(!isNumber(arguments.charAt(0))) {

        messages+="Label '"+currentString+"' without value.,";
        continue;
      }

      if (data[index].isParameter) {

        String value=getNextSubstring();
        //Serial.println("value: "+value);
        char tempArray[12];  //number of characters in a signed long including the '\0' at the end
        value.toCharArray(tempArray,12);

        switch(data[index].varType){

          case byteVar:
            *data[index].pointer.Byte = (byte) atoi(tempArray);
            break;
          case intVar:
            *data[index].pointer.Int =(int) atoi(tempArray);
            break;
          case wordVar:
            *data[index].pointer.Word = (word)  atol(tempArray);
            break;
          case varLong:
            *data[index].pointer.Long = (long)  atol(tempArray);
            break;
          case unsignedvarLong:
            *data[index].pointer.UnsignedLong = (unsigned long)  atol(tempArray);
            break;
          case shortVar:
            *data[index].pointer.Short = (short)  atoi(tempArray);
            break;
          case floatVar:
            *data[index].pointer.Float = (float)  atof(tempArray);
            break;
          case doubleVar:
            *data[index].pointer.Double = (double)  atof(tempArray);
            break;
        }
        messages+="Parameter '"+currentString+"' set to '"+value+"',";
      }
      else
      {
        warnings+="'"+currentString+"' is not a parameter.,";
        getNextSubstring();
      }
    }
    else if (option==get_option){

      if (_manualConnection){

        if (data[index].isParameter) {

          messages+="Parameter '";
        }
        else{

          messages+="Result '";
        }

        messages+=currentString+"': "+dataValueToString(data[index])+",";
      }
      else if (_autoConnection){

        dataString+=currentString+","+dataValueToString(data[index])+",";
      }
    }
  } while (arguments!=")");
}

String LVP::getNextSubstring(){

  String str;
  int aux=arguments.indexOf(',');
  if (aux<0)
  {
    aux=arguments.indexOf(')');
    str = arguments.substring(0,aux); //string until ')'
    arguments=")";
  }
  else{
    str = arguments.substring(0,aux); //string until ','
    arguments=arguments.substring(aux+1); //Discards the ','
  }

  str.trim();
  arguments.trim();

  return str;
}

void LVP::getNewCommand(){

  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (inChar == '\n') {

      command.toLowerCase();

      int aux = command.indexOf('(');
      int aux1 = command.indexOf(')');

      if (((aux>=0&&aux1>=0)&&aux1>aux)&&(aux1-aux)>1) {  //cointains '(' and ')' and '(' comes before of ')'
        arguments=command.substring(aux,aux1+1);
        command=command.substring(0,aux);
        arguments.trim();
      }
      command.trim();

      //For debugging
      //Serial.println("'"+command+"'");
      //Serial.println("'"+arguments+"'");

      selectCommand();
      sendStrings();
      command="";
      arguments="";
      messages="";
      dataString="";
      warnings="";
    }
    else {
      command += inChar;
    }
  }
}

void LVP::selectCommand(){

  //If else chain that determines which function will be called.
  if (command=="auto_connect") {
    establishConnection(auto_option);
    return;
  }
  else if (command=="manual_connect"){

    establishConnection(manual_option);
    return;
  }
  else if (command=="quiet_connect"){
    establishConnection(quiet_option);
    return;
  }
  //Only call a function if there is a connection established
  if (isConnected()){
    if (command=="set") {
      if (arguments=="")
        messages+="Set command without arguments.,";
      else
        processArguments(set_option);                            //Process the arguments. The option defines what is made with those arguments
    }
    else if (command=="get"){
      if (arguments==""){
        sendAll();
      }
      else
        processArguments(get_option);
    }
    else if (command=="disconnect") {
      endConnection();
    }
    else if (command=="reset"){
      resetToDefaultValues();
    }
    else if (command=="test"){
      test();                                                  //Function used to test new stuff
    }
    else if (command!=""){

      int fIndex = searchFunctionFor(command);

      if(fIndex>=0){

        function[fIndex].pointer();
        messages+="Function '"+function[fIndex].label+"' executed.,";

      }
    }
  }
}

void LVP::establishConnection(byte option){

  if (option==manual_option) {
    _autoConnection=false;
    _manualConnection=true;
    _quietConnection=false;
    messages+="Manual connection established.,";
  }
  else if (option==auto_option){
    _autoConnection=true;
    _manualConnection=false;
    _quietConnection=false;
    messages+="Automatic connection established.,";
  }
  else if (option==quiet_option){

    _quietConnection=true;
    _manualConnection=false;
    _autoConnection=false;
  }
}

void LVP::endConnection(){

  messages+="Disconnected.,";
  sendStrings();
  _manualConnection=false;
  _autoConnection=false;
  _quietConnection=false;
}

boolean LVP::isConnected(){

  return ((_manualConnection||_quietConnection)||_autoConnection);

}

//Test if the char is a number
boolean LVP::isNumber (char c){
  if (((c>='0'&&c<='9')||c=='-')||c=='+') { return true; }
  else { return false; }
}

String LVP::getState(){

  if(_manualConnection){
    return "Manual Connection.";
  }
  else if (_autoConnection){
    return "Automatic Connection.";
  }
  else if (_quietConnection){
    return "Quiet Connection.";
  }
  else{
    return "Disconnected.";
  }
}

String LVP::dataValueToString (dataStruct arg) {

  String str="";   //Return object

  switch(arg.varType){

    case byteVar:
      str = valueToString(*arg.pointer.Byte);
      break;
    case intVar:
      str = valueToString(*arg.pointer.Int);
      break;
    case wordVar:
      str = valueToString(*arg.pointer.Word);
      break;
    case varLong:
      str = valueToString(*arg.pointer.Long);
      break;
    case unsignedvarLong:
      str = valueToString(*arg.pointer.UnsignedLong);
      break;
    case shortVar:
      str = valueToString(*arg.pointer.Short);
      break;
    case floatVar:
      str = valueToString(*arg.pointer.Float);
      break;
    case doubleVar:
      str = valueToString(*arg.pointer.Double);
      break;
  }
  return str;
}

static String editForPrint (String input) {

  for (int index=input.indexOf(',');index>=0;index=input.indexOf(',')) {

    input.setCharAt(index,'\n');
  }

  return input;
}

int LVP::searchDataFor(String label){

  int foundIndex=-1;
  String temp;

  //Search through the data vector
  for (byte i=0;i<_currentIndex;i++)
  {
    temp=data[i].label;
    temp.toLowerCase();
    //Action taken if a parameter with the same label as temp is found
    if (temp==label) {
      foundIndex=(int) i;
      break;
    }
  }

  return foundIndex;
}

int LVP::searchFunctionFor(String label){

  int foundIndex=-1;
  String temp;

  //Search through the function vector
  for (byte i=0;i<_currentFIndex;i++)
  {
    temp=function[i].label;
    temp.toLowerCase();
    //Action taken if a parameter with the same label as temp is found
    if (temp==label) {
      foundIndex=(int) i;
      break;
    }
  }
  return foundIndex;
}


void LVP::test() {

}

void LVP::resetToDefaultValues(){

  //Search through the data vector
  for (byte i=0;i<_currentIndex;i++)
  {
    //Action taken if a parameter with the same label as temp is found
    if (data[i].hasDefault) {

      messages+="Parameter '"+data[i].label+"' reset to: ";

      switch(data[i].varType){

        case byteVar:
          *data[i].pointer.Byte=data[i].defaultValue.Byte;
          break;
        case intVar:
          *data[i].pointer.Int=data[i].defaultValue.Int;
          break;
        case wordVar:
          *data[i].pointer.Word=data[i].defaultValue.Word;
          break;
        case varLong:
          *data[i].pointer.Long=data[i].defaultValue.Long;
          break;
        case unsignedvarLong:
          *data[i].pointer.UnsignedLong=data[i].defaultValue.UnsignedLong;
          break;
        case shortVar:
          *data[i].pointer.Short=data[i].defaultValue.Short;
          break;
        case floatVar:
          *data[i].pointer.Float=data[i].defaultValue.Float;
          break;
        case doubleVar:
          *data[i].pointer.Double=data[i].defaultValue.Double;
          break;
      }

      messages+=dataValueToString(data[i])+",";
    }
  }
}

void LVP::sendAll(){

  if(_manualConnection)
  {
    for (byte i=0;i<_currentIndex;i++) {

      if (data[i].isParameter) {
        messages+="Parameter '";
      }
      else{
        messages+="Result '";
      }
      messages+=data[i].label+"': "+dataValueToString(data[i])+",";
    }
  }
  else if (_autoConnection)
  {
    for (byte i=0;i<_currentIndex;i++) {

      dataString+=data[i].label+","+dataValueToString(data[i])+",";
    }
  }
}

void LVP::sendStrings(){

  //Modifying the strings when and where needed

  if (_autoConnection&&messages!="")
    messages="(Messages:,"+messages+")";
  else if (_manualConnection&&messages!="") {
    messages="Messages:,"+messages;
    //For debugging
    //Serial.println(messages);
    messages=editForPrint(messages);
  }

  if (_autoConnection&&warnings!="")
    warnings="(Warnings:,"+warnings+")";
  else if (_manualConnection&&warnings!="") {
    warnings="Warnings:,"+warnings;
    //For debugging
    //Serial.println(warnings);
    warnings=editForPrint(warnings);
  }

  if (_autoConnection&&dataString=="")
    dataString="(void)";
  else if (_autoConnection&&dataString!="")
    dataString="("+dataString+")";
  if (_autoConnection&&messages=="")
    messages="(void)";
  if (_autoConnection&&warnings=="")
    warnings="(void)";

  //Sending

  if (_autoConnection)
    Serial.print(dataString+warnings+messages);
  else if (_manualConnection){
    if (warnings!=""){
      Serial.println(warnings);
      Serial.println();
    }
    if (messages!="")
      Serial.println(messages);
  }
}


