//wifi config
//code inspiration https://diyprojects.io/esp8266-web-client-tcp-ip-communication-examples-esp8266wifi-esp866httpclient/#.Xt4mrdpR2Uk
#include <ESP8266WiFi.h>
//const char* ssid     = "nutipraks";
//const char* password = "minaolennutipraks";      // Password
const char* ssid     = "Nash";// SSID
const char* password = "12345678";      // Password
const char* host = "192.168.46.74";  // Server IP
const int   port = 8888;            // Server Port
const int   watchdog = 500; //watchdog frequency
unsigned long previousMillis = millis(); 
WiFiClient client;

//wemos client configuration pins
int laserpin = D1;
int photopin = A0;
int value;
int threshold = 300;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(laserpin,OUTPUT);
  //permanenetly turned on laser
  digitalWrite(laserpin,HIGH);

  //estabilishing wifi connection
    Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client;
  if (!client.connect(host, port)) {

      Serial.println("Connection to host failed");

      delay(1000);
      return;
  }

  
  // run with intervals
  unsigned long currentMillis = millis();
  if ( currentMillis - previousMillis > watchdog ) {
  previousMillis = currentMillis;

  //read
  value = analogRead(photopin);
  Serial.println(value);

  if (value > threshold){
    Serial.println("OFF");
    client.println("OFF");
  }
  else {
    Serial.println("ON");
    client.println("ON");}
  }
}
