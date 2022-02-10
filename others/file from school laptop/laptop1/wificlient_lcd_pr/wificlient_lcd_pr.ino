
#include <ESP8266WiFi.h>



char ssid[] = "Wemos_AP";           // SSID of your AP
char pass[] = "Wemos_comm";         // password of your AP
int LedPin = D5;
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long currentMillis = 0;
// constants won't change:
const long interval = 5000;
IPAddress server(192, 168, 4, 15); // IP address of the AP
String state;
String answer;
String prox;

void setup() {

  Serial.begin(115200);
  pinMode(LedPin, OUTPUT);
  digitalWrite(LedPin, LOW);
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
  lcd.init();// initialize the lcd
  lcd.backlight();// Backlight ON
  lcd.setCursor(1, 0); // 2nd column,1st row
  lcd.print("Hello!");
  delay(1000);
}

void loop() {
  WiFiClient client;
  client.connect(server, 80);
  answer = "";
  while (client.available())
  {
    char ch = client.read();
    answer += ch;
    delay(2);
  }
  Serial.println("From: " + answer);

  Serial.println(answer);
  answer = client.readStringUntil('\r');


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print ("Wall is:");
  lcd.setCursor(0, 1);
  lcd.print(answer);
  delay(100);
  client.stop();
  delay(1000);

}
