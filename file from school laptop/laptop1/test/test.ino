
#include <ESP8266WiFi.h>
int sensorPin = 0; //define analog pin 0
int value = 0; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(sensorPin); 
  Serial.println(value); // light intensity
                // high values for bright environment
                // low values for dark environment
  delay(100); 
}
