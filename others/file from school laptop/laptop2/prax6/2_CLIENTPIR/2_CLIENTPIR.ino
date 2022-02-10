#include <ESP8266WiFi.h>        // Include the Wi-Fi library

const char* ssid     = "AP1234";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "kana1234";     // The password of the Wi-Fi network
int inputPin = 16;
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
IPAddress server(192, 168, 4, 1);    // the fix IP address of the server
WiFiClient client;

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  pinMode(inputPin, INPUT);     // declare sensor as input

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


  client.connect(server, 80);   // Connection to the serve
  while (client.connected()) {
    val = digitalRead(inputPin);  // read input value
    if (val == HIGH) {            // check if the input is HIGH
      if (pirState == LOW) {
        Serial.println("Motion detected");
        client.println("Mo");  // sends the message to the server
        pirState = HIGH;
      }
    } else {
      client.println("zz");
      if (pirState == HIGH) {
        // We only want to print on the output change, not state
        pirState = LOW;
      }
    }
    delay(1000);
    //client.flush();
    
  }

}
