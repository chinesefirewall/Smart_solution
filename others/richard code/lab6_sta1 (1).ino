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
char ssid[] = "Wemoss";           // SSID of your AP
char pass[] = "Wemos_co";         // password of your AP

int sensorPin = A0;

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
  pinMode(ledPin, OUTPUT);
}

void loop() {
  client.connect(server, 80);
  digitalWrite(ledPin, LOW);
  Serial.println("********************************");
  Serial.print("Byte sent to the AP: ");
//  Serial.println(client.print("Anyo\r"));
//  String saadetud=Serial.readString();
//  client.println(saadetud+"\r");
//  Serial.println(saadetud);
 Serial.println(analogRead(sensorPin));
  delay(20);
  if (analogRead(sensorPin)< 100)
    {
    client.println(String("on")+"\r");
    }
    if (analogRead(sensorPin)> 100)
    {
    client.println(String("off")+"\r");
    }
  client.println(String(cel)+"\r");
  String answer = client.readStringUntil('\r');
  Serial.println("From the AP: " + answer);
  client.flush();
  digitalWrite(ledPin, HIGH);
  client.stop();
  delay(20);
}
