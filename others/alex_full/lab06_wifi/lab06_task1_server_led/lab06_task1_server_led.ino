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

//int led_pin = D6;

#define led_pin D6



String reply;


void setup() {
  
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Wemos_AP_rebriks", "rebriks_sheesh");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  
  Serial.println();
  Serial.println("accesspoint_bare_01.ino");
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);

  
  
}

void loop() {
  //digitalWrite(buzz_pin, LOW);
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("Client connected");
  

  
  String request = client.readStringUntil('\r');
  Serial.println("********************************");
  Serial.println("From the station: " + request);
  client.flush();

  
  if (request.toFloat() <= 20) {
    digitalWrite(led_pin, HIGH);
    reply = "Obstacle detected!";
  } else {
    digitalWrite(led_pin, LOW);
    reply = "Free to go";
  }
  

  
  
  
  Serial.print("Byte sent to the station: ");
  Serial.println(reply);
  client.println(reply + "\r");
  //String saadetud=Serial.readString();
  //client.println(saadetud+"\r");
  //Serial.println(saadetud);
  //digitalWrite(ledPin, HIGH);
}
