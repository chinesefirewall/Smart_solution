
#include <ESP8266WiFi.h>



char ssid[] = "Wemos_AP";           // SSID of your AP
char pass[] = "Wemos_comm";         // password of your AP
int Led = D5;
unsigned long previousMillis = 0;        
unsigned long currentMillis = 0;
// constants won't change:
const long interval = 5000;
IPAddress server(192, 168, 4, 15); // IP address of the AP
String state;
String command1;
void setup() {

  Serial.begin(115200);
  pinMode(Led, OUTPUT);
  digitalWrite(Led, LOW);
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
  WiFiClient client;
  client.connect(server, 80);
  // here I store the state of the led to a variable
  int stateofled = digitalRead(Led);

  String command = "led client";
  client.println(command + "\r");
  command1 = "";
  while (client.available())
  {
    char ch = client.read();
    command1 += ch;
    delay(2);
  }
  Serial.println("From: " + command1);





  Serial.println(command1);

  command1 = client.readStringUntil('\r');
  if (command1 == "led on") {
    previousMillis = millis();
    digitalWrite(Led, HIGH);
    Serial.println("********************************");
    Serial.println("From the station: " + command1);
    state = "on";
    client.flush();

  }
  
 stateofled = digitalRead(Led);
  Serial.println(stateofled);
  Serial.println("From the AP: " + command1);
  if (command1 == "change" && stateofled == 0) {
    Serial.println("From the AP1: " + command1);
    digitalWrite(Led, HIGH);
    client.flush();
    state = "off";
    delay(2000);
  }
  if (command1 == "change" && stateofled == 1) {
    Serial.println("From the AP2: " + command1);
    digitalWrite(Led, LOW);
    client.flush();
    state = "off";
    delay(2000);
  }
  currentMillis = millis();
 // closure of LED after PIR signal in 30 secs 
  if (currentMillis - previousMillis >= 30000) {

    if (state == "on")  {
      state = "off";
      digitalWrite(Led, LOW);
    }
  }
  delay(200);
  client.stop();
  delay(1000);

}
