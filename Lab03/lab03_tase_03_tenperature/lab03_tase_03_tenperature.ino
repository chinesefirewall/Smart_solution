


// sample code from : https://iotboys.com/how-to-use-ds18b20-temperature-sensor/


#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

 float Celcius=0;
 float Fahrenheit=0;

SoftwareSerial mySerial(0,1);//(3,4); OR (0,1); //rx, tx
 
void setup(void)
{
  
  mySerial.begin(9600);
  sensors.begin();
}

void loop(void)
{ 
  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  Fahrenheit=sensors.toFahrenheit(Celcius);
  //mySerial.print(" C  ");
  mySerial.println(Celcius);
  //mySerial.print(" F  ");
  //mySerial.println(Fahrenheit);
  delay(1000);
}



/*
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

float temp_c;

void setup(void)
{
  sensors.begin();  // Start up the library
  mySerial.begin(9600);
}

void loop(void)
{ 
  // Send the command to get temperatures
  sensors.requestTemperatures(); 
  temp_c = sensors.getTempCByIndex(0);
  //print the temperature in Celsius
  mySerial.println(temp_c);
  
  
  
  delay(100);
}

*/
