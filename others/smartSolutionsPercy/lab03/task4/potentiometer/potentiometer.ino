
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

String received_msg;
SoftwareSerial mySerial(3,4); //rx,tx

int potentiometer;

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
mySerial.begin(9600);
}
void loop() {
  if (Serial.available()>0){
     mySerial.println(Serial.readStringUntil('\n'));}
    
  if (mySerial.available()>0){
     received_msg = mySerial.readStringUntil('\n');
     Serial.println(received_msg);
     if (received_msg == "begin"){
       
       potentiometer = analogRead(A0);
       Serial.println(potentiometer);
       mySerial.println(potentiometer);
       
       }
  }
    
 
delay(1000);
}
