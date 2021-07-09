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

#define mov_sensor D2

String answer;
int sensor_val;
String move_status = "mov_false";
bool is_moving = false;

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
  pinMode(mov_sensor, INPUT);
  client.connect(server, 80); 
  
}

void loop() {
  
  /*
  while (client.available()) {
    char ch = client.read();
    answer += ch;
    delay(2);
  }
  */
  //String answer = client.readStringUntil('\r');
  //Serial.println("From the AP: " + answer);
  
  if (digitalRead(mov_sensor) == HIGH) {
    move_status = "mov_true";
    is_moving = true;
  } else if (digitalRead(mov_sensor) == LOW) {
    move_status = "mov_false";
    is_moving = false;
  }
  
  Serial.println("********************************");
  Serial.print("Byte sent to the AP: ");
  Serial.println(move_status);
  client.println(move_status);
  client.flush();
  
  
 
  //client.flush();
  //client.stop();
  delay(1000);
}
