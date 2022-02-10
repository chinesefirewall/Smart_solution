// Ref : http://www.esp8266.com/viewtopic.php?f=28&t=2295&p=13730#p13730

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
WiFiUDP port;
char packetBuffer[255];
unsigned int localPort = 8080;

//sonar pins
const int pingPin = D7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = D6; // Echo Pin of Ultrasonic Sensor
int proximity = 20;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("START");
  Serial.println("START");
  Serial.println("START");
  Serial.println("Client_Proximity");    //prints filename
  WiFi.begin("smart_wifi", "honolulu");
  WiFi.mode(WIFI_STA);
  port.begin(localPort);                    //opens local port 8080
  Serial.print("Connecting to AP, my IP adress is: ");
  Serial.println(WiFi.localIP());             //0.0.0.0
}

//conversion func
long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void loop(){
//read proximity
   long duration,cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   Serial.println(cm);  
//encode in proximity
if (cm < 15){
  proximity = 21;
}
else{
  proximity = 20;
}


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
