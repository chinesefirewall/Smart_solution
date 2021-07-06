//https://arduinogetstarted.com/tutorials/arduino-temperature-sensor
#include <OneWire.h>
#include <DallasTemperature.h>

int msg;
int tempp;

const int SENSOR_PIN = 3; // Arduino pin connected to DS18B20 sensor's DQ pin

OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature sensors(&oneWire); // pass oneWire to DallasTemperature library

float tempCelsius;    // temperature in Celsius

void setup() {
  Serial.begin(9600);

}

void loop() {

sensors.begin();

delay(10);
sensors.requestTemperatures();
tempCelsius = sensors.getTempCByIndex(0);


  
readSerialPort();
{
  {if (msg == 1);
    Serial.println(tempCelsius);    // print the temperature in Celsius
    delay(500);
    }
    
  }

 
  
}

void readSerialPort() {
  
  if (Serial.available() > 0) {
    delay(10);
    while (Serial.available() > 0) {
      msg = Serial.read() - '0';
    }
    Serial.flush();
  }
}
