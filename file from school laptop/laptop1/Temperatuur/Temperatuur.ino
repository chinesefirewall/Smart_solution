#include <SoftwareSerial.h>
#include <Wire.h> 
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float temp = 0.0;
String command;

SoftwareSerial mySerial(4, 5); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  sensors.begin(); 

}

void loop() {

float temp = sensors.getTempCByIndex(0);
sensors.requestTemperatures();
Serial.print("Temperature: ");
Serial.print(temp);
Serial.println("C  |  ");

if (mySerial.available()){
  command = mySerial.readString();
  
  Serial.println(command);
  if(command == "sendtemp"){
    mySerial.println(temp);
  }
  else{
    mySerial.println("Unknown command.");
  }
}

delay(1000);


}

//// First we include the libraries
//#include <OneWire.h> 
//#include <DallasTemperature.h>
//
///********************************************************************/
//// Data wire is plugged into pin 2 on the Arduino 
//#define ONE_WIRE_BUS 2 
///********************************************************************/
//// Setup a oneWire instance to communicate with any OneWire devices  
//// (not just Maxim/Dallas temperature ICs) 
//OneWire oneWire(ONE_WIRE_BUS); 
///********************************************************************/
//// Pass our oneWire reference to Dallas Temperature. 
//DallasTemperature sensors(&oneWire);
///********************************************************************/ 
//void setup(void) 
//{ 
// // start serial port 
// Serial.begin(9600); 
// Serial.println("Dallas Temperature IC Control Library Demo"); 
// // Start up the library 
// sensors.begin(); 
//} 
//void loop(void) 
//{ 
// // call sensors.requestTemperatures() to issue a global temperature 
// // request to all devices on the bus 
///********************************************************************/
// Serial.print(" Requesting temperatures..."); 
// sensors.requestTemperatures(); // Send the command to get temperature readings 
// Serial.println("DONE"); 
///********************************************************************/
// Serial.print("Temperature is: "); 
// Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?  
//   // You can have more than one DS18B20 on the same bus.  
//   // 0 refers to the first IC on the wire 
//   delay(1000); 
//} 
