#include <ESP8266WiFi.h>

const int pir_pin = D5;           // passive infrared sensor pin

unsigned long previousMillis = 0;        // will store last time LED was updated

const long interval = 200;//miliseconds

char ssid[] = "Wemos_AP";           // SSID of your AP
char pass[] = "Wemos_comm";         // password of your AP

IPAddress server(192, 168, 4, 15); // IP address of the AP
WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(pir_pin, INPUT);
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
  //Serial.println("********************************");

  //Serial.println(digitalRead(pir_pin));
  delay(2000);
  if (digitalRead(pir_pin) == HIGH ) {

    Serial.println("Motion detected!");

    client.println("pir detected motion");
    String command = client.readStringUntil('\r');
    //Serial.println("From the AP: " + command);
    client.flush();
    delay(1000);
  }

  if (digitalRead(pir_pin) == LOW ) {
    Serial.println("No movement");

    client.println("pir detected no motion");
    String command = client.readStringUntil('\r');
    //Serial.println("From the AP: " + command);
    client.flush();
    delay(1000);

  }
}
