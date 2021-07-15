
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define WIRE_BUS A0


OneWire oneWire(WIRE_BUS);

DallasTemperature sensors(&oneWire);

int ledPin = 2;
String received_msg;
float temperature;

SoftwareSerial mySerial(3,4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(ledPin, OUTPUT);
  sensors.setResolution(12);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
      mySerial.println(Serial.readStringUntil('\n'));
    }

  if (mySerial.available()>0){
      received_msg = mySerial.readStringUntil('\n');

      if (received_msg == "sensor") {
          sensors.requestTemperatures();
          temperature = sensors.getTempCByIndex(0);
          mySerial.println(temperature);
        }
       else if(received_msg == "ON") {
          flash(200);
        }

       else if(received_msg == "OFF") {
          digitalWrite(ledPin, LOW); 
        }
    }

    delay(1000);
}

void flash(int timing) {
   digitalWrite(ledPin, HIGH);  
   delay(timing);                       
   digitalWrite(ledPin, LOW);   
   delay(timing); 
 }
