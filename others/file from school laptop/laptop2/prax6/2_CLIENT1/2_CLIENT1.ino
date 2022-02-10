#include <ESP8266WiFi.h>        // Include the Wi-Fi library
int LED = 16;
const char* ssid     = "AP1234";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "kana1234";     // The password of the Wi-Fi network

IPAddress server(192, 168, 4, 1);    // the fix IP address of the server
WiFiClient client;

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  WiFi.mode(WIFI_STA);                    // Set as client
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println('\n');
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() {
  client.connect(server, 80);   // Connection to the server

  client.println("Led");  // sends the message to the server
  String answer = client.readStringUntil('\r');   // receives the answer from the server
  Serial.println(answer);

  if (answer == "Led on") {
    digitalWrite(LED, HIGH);
  }

  if (answer == "Led off") {
    digitalWrite(LED, LOW);
  }
  delay(1000);
  //client.flush();
}
