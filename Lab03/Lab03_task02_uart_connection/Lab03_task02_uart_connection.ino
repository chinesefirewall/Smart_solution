 
 // Include the libraries we need
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 7 on the Arduino
#define ONE_WIRE_BUS 6 //7

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device address
DeviceAddress insideThermometer;

int ledPin = 11; //2;
String received_msg;
int led_Status = 0; 

SoftwareSerial mySerial(2,3); // (1,0);//(3,4); //rx, tx


void setup(void)
{
  // start serial port
  mySerial.begin(9600);
  Serial.begin(9600);
  mySerial.println("Dallas Temperature");

  //mySerial.begin(9600);
  pinMode(ledPin, OUTPUT);

  // locate devices on the bus
  //mySerial.println("Locating devices...");
  sensors.begin();
  //mySerial.println("Found ");
  mySerial.println(sensors.getDeviceCount(), DEC);
  //mySerial.println(" devices.");

  // report parasite power requirements
  mySerial.println("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) mySerial.println("ON");
  else mySerial.println("OFF");
  
  if (!sensors.getAddress(insideThermometer, 0)) mySerial.println("Unable to find address for Device 0"); 
  

  // show the addresses we found on the bus
  mySerial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  mySerial.println();

  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(insideThermometer, 11);
 
  mySerial.print("Device 0 Resolution: ");
  mySerial.print(sensors.getResolution(insideThermometer), DEC); 
  mySerial.println();
}

// this function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  

  float tempC = sensors.getTempC(deviceAddress);
  if(tempC == DEVICE_DISCONNECTED_C) 
  {
    mySerial.println("Error: Could not read temperature data");
    return;
  }
  mySerial.print("Temp C: ");
  mySerial.print(tempC);
  //mySerial.print(" Temp F: ");
  //mySerial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
}


void loop(void)
{ 
 
      if (mySerial.available()>0){
        {received_msg = mySerial.readString();
        Serial.println(received_msg);}
  
        if (received_msg == "sensor") {
            // request to all devices on the bus
            mySerial.println("Requesting temperatures...");
            // Send the command to get temperatures
            sensors.requestTemperatures(); 
            
            delay(1000);
            
            // Use a simple function to print out the data
            printTemperature(insideThermometer); 
          }
         else if(received_msg == "ON") {
            if(led_Status == 0) {
                mySerial.println("Turning Led ON");
                digitalWrite(ledPin, HIGH);  
                led_Status = 1;
              } else {
                  mySerial.println("LED is BUSY");
                }
            
            
          }
  
         else if(received_msg == "OFF") {
            if(led_Status == 1) {
                led_Status = 0;
                mySerial.println("Turning Led OFF"); 
                digitalWrite(ledPin, LOW);
                
              } else {
                mySerial.println("Led is already off");
                }
            
          }
  
         else if(received_msg == "status"){
            if (led_Status == 0 ){
                mySerial.println("Led is ON"); 
              } else {
                mySerial.println("Led is OFF");
                }
            
          }
  
         else {
            mySerial.print("Waiting");
          }
      }
  
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) mySerial.print("0");
    mySerial.println(deviceAddress[i], HEX);
  }
}
