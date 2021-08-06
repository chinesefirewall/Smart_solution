#include <ESP8266WiFi.h>
int sensorPin = 0; //define analog pin 0
int value = 0; 
#ifndef STASSID
#define STASSID "robootika"
#define STAPSK  "DigiLaboriArvutiKlass"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "172.17.55.242";
const uint16_t port = 8888;

WiFiClient client;

void setup() {
  
  Serial.begin(230400);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

    Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }
  
}

void loop() {
  value = analogRead(sensorPin); 
  
  // This will send a string to the server
  Serial.println("sending data to server");
  if (client.connected()) {
    if(value>100){
      client.println("appi");
      delay(100);
    }
    else{
      client.println("korras");
      delay(100);
    }
    
  }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 10000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }
  delay(500);
}
