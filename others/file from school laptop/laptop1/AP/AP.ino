/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/soft-access-point-class.rst
 *       https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/soft-access-point-examples.rst
 *       https://github.com/esp8266/Arduino/issues/504
 *  Works with: station_bare_01.ino
 */ 


#include <ESP8266WiFi.h>

WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);

int ledPin = D4;
int led = D2;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Wemos_AP", "Wemos_comm");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  pinMode(ledPin, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.println();
  Serial.println("accesspoint_bare_01.ino");
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());
//  digitalWrite(led, HIGH);
}
void loop() {
  WiFiClient client = server.available();
  if (!client) {return;}
  //digitalWrite(ledPin, LOW);
  String request = client.readStringUntil('\r');
  request.trim();
  
  Serial.println("********************************");
  Serial.println("From the station: " + request);
  client.flush();
  if (request== "LED_OFF"){
    client.println("on\r");
    Serial.println("on");
    digitalWrite(led, LOW);
    } 
  if(request == "LED_ON"){
    client.println("high\r");
    Serial.println("high");
    digitalWrite(led, HIGH);
    }  
  Serial.print("Byte sent to the station: ");
  Serial.println(client.println(request + "ca" + "\r"));
  String saadetud=Serial.readString();
  client.println(saadetud+"\r");
  Serial.println(saadetud);
  digitalWrite(ledPin, HIGH);
}
