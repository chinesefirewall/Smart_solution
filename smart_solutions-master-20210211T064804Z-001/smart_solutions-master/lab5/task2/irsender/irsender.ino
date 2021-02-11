#include <IRremote.h>   

const int sendpin = 2;
IRsend sender;

void setup()  
{ 
  Serial.begin(9600);
}
                               
void loop()  
{ 
  Serial.print("sending zero");
  sender.sendNEC(0xFF9867, 32);           
  delay(600);  
}  
