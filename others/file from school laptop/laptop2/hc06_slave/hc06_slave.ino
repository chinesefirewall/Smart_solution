#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

SoftwareSerial bt(2,3);

#define ONE_WIRE_BUS 6
float tempC;
#define SENSOR_RESOLUTION 9
#define SENSOR_INDEX 0

OneWire onewire(ONE_WIRE_BUS);
DallasTemperature sensors(&onewire);
DeviceAddress sensorDeviceAddress;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Arduino for HC-06");
  bt.begin(9600);
  Serial.println("BT seial waiting");
  sensors.begin();
  sensors.getAddress(sensorDeviceAddress, 0);
  sensors.setResolution(sensorDeviceAddress, SENSOR_RESOLUTION);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures(); 
  float tempC = sensors.getTempCByIndex(SENSOR_INDEX);
  
  if (bt.available()){
    Serial.println(bt.readString());
    Serial.println(tempC);
    delay(1000);
  }
  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    bt.println(Serial.readString());
}
