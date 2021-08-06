//hc-06
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

#define temppin 8
int temp = 0;
float t = 0;
String input;
OneWire oneWire(temppin);
DallasTemperature sensors(&oneWire);
SoftwareSerial mySerial(3, 2); // RX, TX
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // speed 9600 bps
  sensors.begin();
  mySerial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print("Celcius temperature: ");
  //Serial.println(sensors.getTempCByIndex(0));
  Serial.println(mySerial.readString());

  sensors.requestTemperatures();
  t = sensors.getTempCByIndex(0);
  Serial.println(t);
  mySerial.println(t);
  delay(1000);

}
