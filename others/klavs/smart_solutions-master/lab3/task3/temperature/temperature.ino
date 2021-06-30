
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define wire  A0

OneWire oneWire(wire);

DallasTemperature sensors(&oneWire);

String rec_msg;
SoftwareSerial mySerial(2,3); //rx,tx


int temp;

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
mySerial.begin(9600);
sensors.begin();
sensors.setResolution(12);
}
void loop() {
  if (Serial.available()>0){
     mySerial.println(Serial.readStringUntil('\n'));}
    
  if (mySerial.available()>0){
     rec_msg = mySerial.readStringUntil('\n');
     
     if (rec_msg == "start"){
      sensors.requestTemperatures();
       temp = sensors.getTempCByIndex(0);
       Serial.print(temp);
         mySerial.println(temp);}
  }
    
 
delay(1000);
}
