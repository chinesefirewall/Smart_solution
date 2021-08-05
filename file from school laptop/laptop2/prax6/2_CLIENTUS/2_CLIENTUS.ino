#include <ESP8266WiFi.h>        // Include the Wi-Fi library
int echoPin = 16;
int trigPin = 5;
long duration, distance; // Duration used to calculate distance
const char* ssid     = "AP1234";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "kana1234";     // The password of the Wi-Fi network
IPAddress server(192, 168, 4, 1);    // the fix IP address of the server
WiFiClient client;

void setup()
{
  Serial.begin (115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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

void loop()
{
  client.connect(server, 80);   // Connection to the server

  while (client.connected()) {
    /* The following trigPin/echoPin cycle is used to determine the
      distance of the nearest object by bouncing soundwaves off of it. */
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    //Calculate the distance (in cm) based on the speed of sound.
    distance = duration / 58.2;
    Serial.println(distance);

    if (distance < 20) {
      client.println("OnOff");
    }
    else {
      client.println("us");
    }
    //Delay 50ms before next reading.
    delay(1000);
    //client.flush();
    
  }

}
