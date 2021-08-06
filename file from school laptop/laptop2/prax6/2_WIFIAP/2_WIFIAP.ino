#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <SoftwareSerial.h>

const char *ssid = "AP1234"; // The name of the Wi-Fi network that will be created
const char *password = "kana1234";   // The password required to connect to it, leave blank for an open network
WiFiServer server(80);
boolean ledState = false;
boolean pirState = false;
unsigned long currentTime;
unsigned long ledTime;
void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer
  server.begin();
}

void loop() {
  currentTime = millis();
  if (currentTime - ledTime >= 20000 && ledState == true) {
    ledState = false;
    ledTime = currentTime;
  }

  WiFiClient client = server.available();

  if (!client) {
    return;
  }

  String request = client.readStringUntil('\r');    // receives the message from the client
  client.flush();
  Serial.print("From client: ");
  Serial.println(request);

  if (request == "Mo" && ledState == false) {
    ledState = true;
    ledTime = millis();
  }

  else if (request == "Led") {
    if (ledState == true) {
      client.println("Led on");
    }
    else if (ledState == false) {
      client.println("Led off");
    }
  }

  else if (request == "OnOff" && ledState == false) {
    ledState = true;
    
  }
  else if (request == "OnOff" && ledState == true) {
    ledState = false;
  }

}
