/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/soft-access-point-class.rst
 *       https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/soft-access-point-examples.rst
 *       https://github.com/esp8266/Arduino/issues/504
 *  Works with: station_bare_01.ino
 */ 


#include <ESP8266WiFi.h>
#include <ctime>
#include <iostream>
using namespace std;

WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);
int pirstate = 0;
int switchstate = 1;
int switchstater = 1;
unsigned long myTime1;
unsigned long myTime2;

byte ledPin = 2;
////////////////////////////
#ifndef STASSID
#define STASSID "robootika"
#define STAPSK  "DigiLaboriArvutiKlass"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;


const char* host = "172.17.54.208";
const uint16_t port = 81;
////////////////////////////////
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Wemoss", "Wemos_co");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  pinMode(ledPin, OUTPUT);
  Serial.println();
  Serial.println("accesspoint_bare_01.ino");
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());



 
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {return;}
  digitalWrite(ledPin, LOW);
  String request = client.readStringUntil('\r');
  Serial.println("********************************");
  Serial.println("From the station: " + request);
  
    
  client.println(String(switchstate)+"\r");
  
  
  client.flush();
//  Serial.print("Byte sent to the station: ");
//  Serial.println(client.println(request + "ca" + "\r"));
  String saadetud=Serial.readString();
  //client.println(saadetud+"\r");
  //client.println(String("hmm")+"\r");


  
  if (request == "on")
  {
    switchstater = 1;
  }
  Serial.println(switchstater);
  Serial.println(switchstate);
    if ((request == "off") && (switchstater == 1))
  {
    switchstate = switchstate*-1;
    switchstater = 0;
    delay(20);
  }
  if (request == "motion"){
   myTime1 = millis();
   pirstate = 1;
   switchstate = 1;
   delay(20);
  }
  myTime2 = millis();
  Serial.println(myTime2-myTime1);
  if (((myTime2-myTime1) > 5000) && ((myTime2-myTime1) < 8000)) {
    pirstate = 0;
    switchstate = -1;
    
  Serial.println("hmm");
  }
  

  
  Serial.println(saadetud);
  digitalWrite(ledPin, HIGH);

  
}
