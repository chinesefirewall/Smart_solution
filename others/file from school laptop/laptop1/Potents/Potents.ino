//Ekraani osa voetud sellelt lingilt https://randomnerdtutorials.com/guide-for-oled-display-with-arduino/

#include <SoftwareSerial.h>
#include <Wire.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);




String command;

SoftwareSerial mySerial(4, 5); // RX, TX
int value = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(100);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  
}

void loop() {

int value = analogRead(A0);
Serial.print("Pinge: ");
Serial.print(value);
Serial.println("V  |  ");

float valueFloat = float(value);

float voltage = valueFloat*5/1023;
String text = String(voltage,3);

display.clearDisplay();

display.setTextSize(3);
display.setTextColor(WHITE);
display.setCursor(0, 10);
display.println(text);
display.display(); 

if (mySerial.available()){
  command = mySerial.readString();
  
  Serial.println(command);
  if(command == "sendvoltage"){
    mySerial.println(value);
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
