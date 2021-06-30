// Ref : http://www.esp8266.com/viewtopic.php?f=28&t=2295&p=13730#p13730

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
WiFiUDP port;
char packetBuffer[255];
unsigned int localPort = 8080;

//PIR
int pirPin = D2;
int val;
int pirState = 10; //11 yes 10 no
int calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause = 1000;
boolean lockLow = true;
boolean takeLowTime;
int PIRValue = 0;
int tmp = 10;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("START");
  Serial.println("START");
  Serial.println("START");
  Serial.println("Client_Motion");    //prints filename
  WiFi.begin("smart_wifi", "honolulu");
  WiFi.mode(WIFI_STA);
  port.begin(localPort);                    //opens local port 8080
  Serial.print("Connecting to AP, my IP adress is: ");
  Serial.println(WiFi.localIP());             //0.0.0.0
  //PIR
  pinMode(pirPin, INPUT);
}

void PIRSensor() {
   if(digitalRead(pirPin) == HIGH) {
      if(lockLow) {
         PIRValue = 1;
         lockLow = false;
         Serial.println("Motion detected.");
         tmp = 11;
      }
      takeLowTime = true;
   }
   if(digitalRead(pirPin) == LOW) {
      if(takeLowTime){
         lowIn = millis();takeLowTime = false;
      }
      if(!lockLow && millis() - lowIn > pause) {
         PIRValue = 0;
         lockLow = true;
         Serial.println("Motion ended.");
         tmp = 10;
      }
   }
}

void loop(){
//read motion
    PIRSensor();
    int motion = tmp;

//Send data to the IP address & port of the AP
    port.beginPacket("192.168.4.1",8080);
    char msg[3];                          
    sprintf(msg, "%d", motion); // (int)T, (int)(T*100)%100);
    port.write(msg);
    port.write("\r\n");
    port.endPacket();
    Serial.print("Sending following msg to AP ->");
    Serial.print(msg);
    delay(2000);
 
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
