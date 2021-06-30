/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.rst
 *  Works with: accesspoint_bare_01.ino
 */

#include <ESP8266WiFi.h>

//LM35 stuff
int val;
int tmpPin=0;
float mv,cel;

byte ledPin = 2;
char ssid[] = "robootika";           // SSID of your AP
char pass[] = "DigiLaboriArvutiKlass";         // password of your AP
  //DigiLaboriArvutiKlass
int led = D3;


String request;
//IPAddress ip;
WiFiServer server(22000);
//PAddress IP(ip[0],ip[1],ip[2],ip[3]);
//IPAddress mask = (255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  server.begin();
  pinMode(ledPin, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.println();
  Serial.println("Connected!");
  Serial.println("accesspoint_bare_01.ino");
  Serial.println("Server started.");
  Serial.print("IP: ");     
  Serial.println(WiFi.localIP());
  digitalWrite(led, LOW);
 // ip = WiFi.localIP();
  //String part1 = getValue(IP,'.',0);
  //String part2 = getValue(IP,'.',1);
  //String part3 = getValue(IP,'.',2);
  //String part4 = getValue(IP,'.',3);
  //String ip_new = part1 + ',' + part2 + ',' + part3 + ',' + part4;
  //Serial.println(ip[0]);
  //WiFiServer server(80);
//  IPAddress IP(ip[0],ip[1],ip[2],ip[3]);
  //IPAddress mask = (255, 255, 255, 0);
 // Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());
}


void loop() {
  WiFiClient client = server.available();
  if (!client) {return;}
  digitalWrite(ledPin, LOW);
  //if(client.available())
  //{
  //request = client.readString();
  //Serial.println("********************************");
  //Serial.println("From the station: " + request);
  //}
  //client.flush();
  //Serial.println("Byte sent to the station: \r");
  //Serial.println(client.println(request + "ca" + "\r"));
  //String saadetud=Serial.readString();
  String answer = client.readStringUntil('\r');
  Serial.println("From the station: " + answer);
  client.flush();
  //Serial.println(saadetud);
  digitalWrite(ledPin, HIGH);
  if (answer.toInt() > 100) {
     digitalWrite(led, HIGH);
     client.println("Obstacle!");
    }
  else {
     digitalWrite(led, LOW);
     client.println("OK!");
    }
  
}
