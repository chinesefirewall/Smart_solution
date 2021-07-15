// Bluetooth AT slave config and communication code
// for Arduino Nano
// use software serial on pins D2. D3 (rx,tx resp.) via level shifter
// use D4 for EN-pin via level shifter
// use D5 for VCC-pin
// use temp sensor at A0

#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 7


OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);
SoftwareSerial bt(2,3); // rx,tx

int temperature;

//String slave_name="np-05-23";
String received_msg;

void setup() {

  sensors.begin();
  sensors.setResolution(11);
 
  Serial.begin(9600);
  Serial.println("Enter At commands: ");
  
  // BT AT mode goes at 9600 baud
    bt.begin(9600);
  
  Serial.println("initialising slave HC-06 ...");

}

void loop() {
  // put your main code here, to run repeatedly:
if(bt.available())
{
    received_msg = bt.readString();
    Serial.println("message received: ");
    Serial.println(received_msg);

    if (received_msg == "1\n") {
        Serial.println("starting the measurments");
        sensors.requestTemperatures();
        temperature = sensors.getTempCByIndex(0);
        Serial.print("received measurments");
        Serial.print(temperature);
        //sending measurments
        bt.print(temperature);
        Serial.println(bt.readString());
      }
     
    
    
//display incoming message
  //Serial.println(bt.read());
}
if(Serial.available())
{
  bt.println(Serial.readString());
}
}

void atcommand(const String _atcommand)
{
  Serial.print(_atcommand);
  bt.print(_atcommand);
  delay(1000);
  while(bt.available())
    Serial.write(bt.read());
}
