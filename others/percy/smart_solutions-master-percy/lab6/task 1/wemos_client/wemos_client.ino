//wifi config
//code inspiration https://diyprojects.io/esp8266-web-client-tcp-ip-communication-examples-esp8266wifi-esp866httpclient/#.Xt4mrdpR2Uk
#include <ESP8266WiFi.h>
const char* ssid     = "ARA_PRAX";      // SSID
const char* password = "Nutirobot!";      // Password
const char* host = "192.168.10.134";  // Server IP
const int   port = 8888;            // Server Port
const int   watchdog = 500; //watchdog frequency
unsigned long previousMillis = millis(); 
WiFiClient client;

//client of laser lab 6 task 1
int laserpin = D1;
int photopin = A0;
int value;
int threshold = 80;

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
    Serial.println("LED_OFF");
    client.println("LED_OFF");
  }
  else {
    Serial.println("LED_ON");
    client.println("LED_ON");}
  }
}
