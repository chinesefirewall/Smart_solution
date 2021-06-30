#include <SoftwareSerial.h>

const int relaypin = 10;

String rec_msg;
SoftwareSerial mySerial(2,3); //rx,tx

void setup() {
// put your setup code here, to run once:
pinMode(relaypin,OUTPUT);
digitalWrite(relaypin,HIGH);
Serial.begin(115200);
mySerial.begin(115200);
}

void loop() {
  //console where to write something
  if (Serial.available()>0){
     mySerial.println(Serial.readStringUntil('\n'));}

  //receiver part controlling the led
  if (mySerial.available()>0){
     rec_msg = mySerial.readStringUntil('\n');
     
     if (rec_msg == "ON"){
       Serial.print("LED TURNED ON");
       mySerial.println("LED TURNED ON");}
         
     if (rec_msg == "OFF"){
       Serial.print("LED TURNED OFF");
       mySerial.println("LED TURNED OFF");}
  }
    
 
delay(1000);
}
