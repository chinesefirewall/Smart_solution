#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define DS18B20 8

OneWire ourWire(DS18B20);
DallasTemperature sensor(&ourWire);
SoftwareSerial bt(3, 2); // rx,tx

int counter = 0;
String inputString, outputString, sensorData;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("== initialising HC-05 BT module as slave...==");
  // switch to BT comunication mode at 9600 baud
  bt.begin(9600);
  Serial.println("== entering into the communication mode...the table is yours ;)...==");
  delay(1000);
}


void loop() {
  // put your main code here, to run repeatedly:

  // read temperature sensor
  sensor.requestTemperatures();

  sensorData = sensor.getTempCByIndex(0);

  // main communication happens here
  if (bt.available())
  {
    inputString = bt.readString();
    inputString.trim();
    delay(100); // set the delay long enough to read in the entire incoming buffer
    Serial.println(inputString);
    if (inputString == "send") // master is expected to send this keyword
    {
      Serial.print(sensorData);
      Serial.println(" °C");
      bt.print(sensorData);
    }
  }

  if (Serial.available())
  {
    outputString = Serial.readString();
    Serial.print("== local: ");
    Serial.println(outputString);
    bt.print(outputString);
  }
  delay(1000);
}
