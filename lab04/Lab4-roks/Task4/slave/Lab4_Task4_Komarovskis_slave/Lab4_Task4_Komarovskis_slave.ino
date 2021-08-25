
#include <SoftwareSerial.h>
#include <DallasTemperature.h>

SoftwareSerial bt(2,3); // rx,tx

#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);


String rec;

int counter=0;
String inputString,outputString;

void setup() {

  sensor.begin();
  
  bt.begin(9600);
  Serial.begin(9600);
}

void loop(){
  if(bt.available()){
    rec = bt.readString();
    if(rec == "send"){
      sensor.requestTemperatures();
      bt.print(sensor.getTempCByIndex(0));
    }
  }
  //Serial.println(sensor.getTempCByIndex(0));

}
