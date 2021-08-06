#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 6 //7


OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

String received_msg;
SoftwareSerial mySerial(2,3); //rx, tx


int temperature;

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
mySerial.begin(9600);
sensors.begin();
sensors.setResolution(12);
}
void loop() {
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  Serial.print(temperature);

  if (Serial.available()>0){
     mySerial.println(Serial.readStringUntil('\n'));
     }
    
  if (mySerial.available()>0){
     received_msg = mySerial.readStringUntil('\n');
     
     if (received_msg == "begin"){
        sensors.requestTemperatures();
        temperature = sensors.getTempCByIndex(0);
        Serial.print(temperature);
        mySerial.println(temperature);
        
        }
  }
    
 
delay(1000);
}
