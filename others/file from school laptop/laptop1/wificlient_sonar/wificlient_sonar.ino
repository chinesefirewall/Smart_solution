#include <ESP8266WiFi.h>

int echo_pin = 4;
int trig_pin = 0;
int delay_us = 10; // <--- YOU HAVE TO FIND THE CORRECT VALUE FROM THE DATASHEET
long distance_mm = 0;
long duration_us;

char ssid[] = "Wemos_AP";           // SSID of your AP
char pass[] = "Wemos_comm";         // password of your AP

IPAddress server(192, 168, 4, 15); // IP address of the AP
WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  
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
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
}

void loop() {
  client.connect(server, 80);
  Serial.println("********************************");
  
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(delay_us);
    digitalWrite(trig_pin, LOW);
    

    duration_us = pulseIn(echo_pin, HIGH);
    
    distance_mm = duration_us; //(duration_us*0.34)/2;

  if (distance_mm <= 50) {

    Serial.println("too close!");
    Serial.println(distance_mm);
    client.println("sonar signal");

    client.flush();
    delay(2000);
  }

  if (distance_mm >= 50) {
    delay(500);
  }
}
