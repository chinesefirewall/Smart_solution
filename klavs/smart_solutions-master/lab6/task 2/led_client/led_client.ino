// Ref : http://www.esp8266.com/viewtopic.php?f=28&t=2295&p=13730#p13730

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
WiFiUDP port;
char packetBuffer[255];
unsigned int localPort = 8080;

//led pins
const int ledPin = D1;
int ledStatus = 30;
int cmd;
int command[2];

void setup() {
  //have to set before wifi
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);

  //serial and wifisetup
  Serial.begin(115200);
  delay(2000);
  Serial.println("START");
  Serial.println("START");
  Serial.println("START");
  Serial.println("Client_LED");    //prints filename
  WiFi.begin("smart_wifi", "honolulu");
  WiFi.mode(WIFI_STA);
  delay(1000);
  port.begin(localPort);                    //opens local port 8080
  Serial.print("Connecting to AP, my IP adress is: ");
  Serial.println(WiFi.localIP());             //0.0.0.0
  delay(1000);
}
void loop(){
//Send data to the IP address & port of the AP
    port.beginPacket("192.168.4.1",8080);
    char msg[3];                          
    sprintf(msg, "%d", ledStatus);
    port.write(msg);
    port.write("\r\n");
    port.endPacket();
    Serial.print("Sending following msg to AP ->");
    Serial.print(msg);
    delay(1000);
 
//if there is data available from AP, read a packet received from AP
    int packetSize = port.parsePacket();
    Serial.print("  Received response from AP (Size/data): ");
    Serial.print(packetSize);                                   //returned packet size = 2
    Serial.print(" / ");
 
 if (packetSize)
  {
    int len = port.read(packetBuffer, 255);     //read AP packetBuffer Data
    if (len > 0)
    //packetBuffer[len-1] = 0;
    Serial.print(packetBuffer);  //print data sent from AP

    //store for conversion
    command[1] = packetBuffer[0];
    command[2] = '\0';

    cmd = atoi(packetBuffer);
    Serial.println(cmd);
    Serial.println(cmd);

    
    //turn LED ON/OFF
    if (cmd == 0){
      Serial.println("h1");
      digitalWrite(ledPin, LOW);
      ledStatus = 30;
    }
    if (cmd == 1){
      digitalWrite(ledPin, HIGH);
      ledStatus = 31;
    }
  }
    Serial.println("");
}
//- See more at: http://www.esp8266.com/viewtopic.php?f=29&t=4006#sthash.JrbgCVdt.Q4ILiGvV.dpuf
