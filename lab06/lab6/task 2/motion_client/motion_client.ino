// Ref : http://www.esp8266.com/viewtopic.php?f=28&t=2295&p=13730#p13730

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
WiFiUDP port;
char packetBuffer[255];
unsigned int localPort = 8080;

//PIR
const int pir_pin = 2;
bool in_motion = false;

int val;
int pirState = 10; //11 yes 10 no
int tmp = 10;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("START");
  Serial.println("START");
  Serial.println("START");
  Serial.println("Client_Motion");    //prints filename
  WiFi.begin("smart_solution", "password");
  WiFi.mode(WIFI_STA);
  port.begin(localPort);                    //opens local port 8080
  Serial.print("Connecting to AP, my IP adress is: ");
  Serial.println(WiFi.localIP());             //0.0.0.0
  //PIR
  pinMode(pir_pin, INPUT);
}



void loop(){
    //read motion
    if(digitalRead(pir_pin) == HIGH && !in_motion){
      Serial.println("Motion detected!");
      in_motion = true;
      tmp = 10;
    }

    if (digitalRead(pir_pin) == LOW && in_motion) {
        Serial.println("No movement anymore");
        in_motion = false;
        tmp = 11;
      }
      
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
