/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.rst
 *  Works with: accesspoint_bare_01.ino
 */

#include <ESP8266WiFi.h>

//LM35 stuff

long unsigned previousMillis, currentMillis;
int interval = 30000; // ms??


char ssid[] = "Wemos_AP_rebriks";           // SSID of your AP
char pass[] = "rebriks_sheesh";         // password of your AP

//int echo_pin = 12;
//int trig_pin = 14;

#define led_pin D6


String led_status = "led_off";
String reply;

IPAddress server(192,168,4,54);     // IP address of the AP
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
  pinMode(led_pin, OUTPUT);
  
  client.connect(server, 80);
}

void loop() {
  
  
  /*
  while (client.available()) {
    char ch = client.read();
    reply += ch;
    delay(2);
  }
  */
  client.println(led_status);
  client.flush();

  int led_pin_state = digitalRead(led_pin);
  
  String reply = client.readStringUntil('\r');
  Serial.println("********************************");
  Serial.println("From the AP: " + reply);
  reply.trim();
  if (reply == "on") {
    digitalWrite(led_pin, HIGH);
 
  } else if (reply == "off") {
    digitalWrite(led_pin, LOW);
  }
  
  /*
  if (reply.indexOf("1") == -1) {
    if (reply == "on") {
    previousMillis = millis();
    digitalWrite(led_pin, HIGH);
    //led_status = "led_on";
    //delay(2000);
    } 
  }
  if (reply.indexOf("1") != -1) {
    if (led_pin_state == 0) {
      
      digitalWrite(led_pin, HIGH);
    
    //delay(2000);
    } 
    else if (led_pin_state == 1) {
      digitalWrite(led_pin, LOW);
    }
  }
  */

  

  
  
  /*
  currentMillis = millis();

  if (currentMillis - previousMillis >=interval) {
    digitalWrite(led_pin, LOW);
  }
  */
  Serial.print("Byte sent to the AP: ");
  Serial.println(led_status);
  //client.println(led_status + "\r");
  
  //client.flush();
  //delay(250);
  //client.stop();
  delay(2000);
}
