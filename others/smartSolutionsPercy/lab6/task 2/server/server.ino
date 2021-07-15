#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//somthing
WiFiUDP port;
char packetBuffer[255];
int command[3];

//wifi conf
const char *ssid = "smart_wifi";
const char *password = "honolulu";
const int MAXclients = 3;

IPAddress local_IP(192,168,4,1);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

IPAddress IPClient1(192,168,4,2);            //IP address allocated to client1
IPAddress IPClient2(192,168,4,3);            //IP address allocated to client2
IPAddress IPClient3(192,168,4,4);            //IP address allocated to client3

WiFiServer server(8080);
WiFiClient APclient[MAXclients];

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  delay(1000);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.printf("MAC address = %s\n", WiFi.softAPmacAddress().c_str());
  
  server.begin(); 
}

void loop() {
  //reading data and deciding what to do
   int packetSize = port.parsePacket();                   //reads packetSize form client
   Serial.print("Received from client(IP/Size/Data):\t ");
   Serial.print(port.remoteIP());                         //reads & prints client IP address
   Serial.print(" / ");
   Serial.print(packetSize);                             //reads & prints packetSize
   Serial.print(" / ");

}
