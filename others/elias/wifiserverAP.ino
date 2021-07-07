


#include <ESP8266WiFi.h>

WiFiServer server(80);
IPAddress IP(192, 168, 4, 15);
IPAddress mask(255, 255, 255, 0);
String command;
String command1;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Wemos_AP", "Wemos_comm");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  Serial.println();
  Serial.println("accesspoint_bare_01.ino");
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());
}

void loop() {

  WiFiClient client = server.available();
  if (!client) {return; }



  String request = client.readStringUntil('\r');
  if (request == "PIR") {
    Serial.println("********************************");
    Serial.println("From the station: " + request);
    Serial.println("LED is on");
    Presponse= "led on";
  }

  Serial.println("request: " +  request);

  if (request == "led client" &&  Presponse == "led on") {

    client.println(Presponse  + "\r");
    Serial.println("PIR signal : " +  Presponse );
    Presponse  = " ";
    client.flush();

  }

  if (request == "sonar") {
    Serial.println("********************************");
    Serial.println("From the station: " + request);
    Serial.println("change state");
    Sresponse = "change";
    delay(1000);
  }

  Serial.println("request: " +  request);

  if (request == "led client" &&  Sresponse== "change") {
    command1 = "change";
    client.println(Sresponse + "\r");
    Serial.println("Sonar response: " +  Sresponse);
    delay(100);

    Sresponse = " ";
    client.flush();
  }


}
