#include<LVP.h>

#define numDados 12
#define baudRate 38400

int a=10,b=5,soma,sub,divi,mult;
float c=5.5,d=2.7,soma1,sub1,divi1,mult1;
LVP dados(numDados,baudRate);

void setup()
{
  dados.initialize();
  
  dados.addParameter("a",&a,a);
  dados.addParameter("b",&b);
  dados.addResult("a+b",&soma);
  dados.addResult("a-b",&sub);
  dados.addResult("a/b",&divi);
  dados.addResult("a*b",&mult);
  
  dados.addParameter("c",&c,c);
  dados.addParameter("d",&d);
  dados.addResult("c+d",&soma1);
  dados.addResult("c-d",&sub1);
  dados.addResult("c/d",&divi1);
  dados.addResult("c*d",&mult1);
}

void loop(){
   
  soma=a+b;
  sub=a-b;
  divi=a/b;
  mult=a*b;
  
  soma1=c+d;
  sub1=c-d;
  divi1=c/d;
  mult1=c*d;
  
  /*quietConnection test
  Serial.print("c: ");
  Serial.println(c);
  Serial.print("d: ");
  Serial.println(d);
  delay(1000);
  */
  
  /* connection tests
  Serial.print("isConnected(): ");
  Serial.println(dados.isConnected());
  Serial.print("getState(): ");
  Serial.println(dados.getState());
  delay(1000);
  */
  
  dados.getNewCommand();   
}
