
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

String rec_msg;
SoftwareSerial mySerial(2,3); //rx,tx

int potent;

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
mySerial.begin(9600);
}
void loop() {
  if (Serial.available()>0){
     mySerial.println(Serial.readStringUntil('\n'));}
    
  if (mySerial.available()>0){
     rec_msg = mySerial.readStringUntil('\n');
     
     if (rec_msg == "start"){

       potent = analogRead(A0);
       Serial.print(potent);
         mySerial.println(potent);}
  }
    
 
delay(1000);
}
