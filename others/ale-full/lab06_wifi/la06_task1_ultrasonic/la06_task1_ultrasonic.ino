/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.rst
 *  Works with: accesspoint_bare_01.ino
 */

#include <ESP8266WiFi.h>

//LM35 stuff


char ssid[] = "Wemos_AP_rebriks";           // SSID of your AP
char pass[] = "rebriks_sheesh";         // password of your AP

//int echo_pin = 12;
//int trig_pin = 14;

#define echo_pin D6
#define trig_pin D5

long duration_us, cm;

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println("station_bare_01.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  //pinMode(ledPin, OUTPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  
}

void loop() {
  client.connect(server, 80);
  
  Serial.println("********************************");
  
  //Serial.println(client.print("Anyo\r"));
  //String saadetud = Serial.readString();
  //client.println(saadetud+"\r");
  //Serial.println(saadetud);
  
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  duration_us = pulseIn(echo_pin, HIGH);
 
  cm = duration_us / 58.0;
  Serial.print("Byte sent to the AP: ");
  Serial.println(cm);
  client.println(String(cm)+"\r");
  String answer = client.readStringUntil('\r');
  Serial.println("From the AP: " + answer);
  client.flush();
  //client.stop();
  delay(200);
}
