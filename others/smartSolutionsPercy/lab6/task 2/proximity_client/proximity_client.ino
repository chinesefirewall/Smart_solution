// Ref : http://www.esp8266.com/viewtopic.php?f=28&t=2295&p=13730#p13730
#include "Adafruit_VL53L0X.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
WiFiUDP port;
char packetBuffer[255];
unsigned int localPort = 8080;
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

int proximity = 10;
int proximity_mm;

void setup() {
  
  Serial.begin(115200);

  // proximity sensor setup
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
  
  delay(2000);
  Serial.println("START");
  Serial.println("START");
  Serial.println("START");
  Serial.println("Client_Proximity");    //prints filename
  WiFi.begin("smart_solution", "password");
  WiFi.mode(WIFI_STA);
  port.begin(localPort);                    //opens local port 8080
  Serial.print("Connecting to AP, my IP adress is: ");
  Serial.println(WiFi.localIP());             //0.0.0.0
}


void loop(){
  
  //read proximity
   VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    proximity_mm = measure.RangeMilliMeter;
    Serial.print("Distance (mm): "); 
    Serial.println(proximity_mm);
    
  } else {
    Serial.println(" out of range ");
    proximity_mm = 1;
  }
    
  //encode in proximity
  if (proximity_mm < 90 && proximity_mm > 30 ){
    proximity = 11;

    //Send data to the IP address & port of the AP
    port.beginPacket("192.168.4.1",8080);
    char msg[3];                          
    sprintf(msg, "%d", proximity);
    port.write(msg);
    port.write("\r\n");
    port.endPacket();
    Serial.print("Sending following msg to AP ->");
    Serial.print(msg);
    delay(2000);
  }
  else{
    proximity = 10;
    //Send data to the IP address & port of the AP
    port.beginPacket("192.168.4.1",8080);
    char msg[3];                          
    sprintf(msg, "%d", proximity);
    port.write(msg);
    port.write("\r\n");
    port.endPacket();
    Serial.print("Sending following msg to AP ->");
    Serial.print(msg);
    delay(2000);
  }



 
//if there is data available from AP, read a packet received from AP
    int packetSize = port.parsePacket();
    Serial.print("  Received response from AP (Size/data): ");
    Serial.print(packetSize);                                   //returned packet size = 33
    Serial.print(" / ");
 
 if (packetSize)
  {
    int len = port.read(packetBuffer, 255);     //read AP packetBuffer Data
    if (len > 0)
    packetBuffer[len-1] = 0;
    Serial.print(packetBuffer);  //print data sent from AP    
  }
    Serial.println("");
}
//- See more at: http://www.esp8266.com/viewtopic.php?f=29&t=4006#sthash.JrbgCVdt.Q4ILiGvV.dpuf
