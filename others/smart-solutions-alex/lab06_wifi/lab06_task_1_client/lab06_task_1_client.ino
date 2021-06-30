

#include <ESP8266WiFi.h>

// SENSOR

const int echo_pin = 6;
const int trig_pin = 7;

// WIFI
char ssid[] = "ut-public";
char pass[] = "";


IPAddress server(192, 168, 4, 15);
WiFiClient client;


long duration, cm;

String answer;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.println("[INFO] Connecting to SERVER");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("...");
    delay(500);
    
  }
  
  Serial.println("[SUCCESS] Wifi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("******************");
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void loop() {
  client.connect(server, 80);
  //

  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);
  cm = duration_to_cm(duration);

  Serial.print("Distance: ");
  Serial.println(cm);
  
  client.println(String(cm) + "\r");
  answer = client.readStringUntil('\r');
  Serial.println("REPLY FROM AP: " + answer);
  client.flush();

  client.stop();
    
  delay(1000);
}


long duration_to_cm(long duration) {
  return duration / 29 /2;
}
