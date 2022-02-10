#include <FastLED.h>
#include <OneWire.h>
#include <DallasTemperature.h>
String command;

#define ONE_WIRE_BUS 7
#define LED_PIN     9
#define NUM_LEDS    20
CRGB leds[NUM_LEDS];

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors (&oneWire);

float celsius = 0;
void setup() {
  sensors.begin();
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

}

void loop() {
  sensors.requestTemperatures();
  celsius = sensors.getTempCByIndex(0);
  //float celsius = analogRead(celsius);
  //float temperatureC = (voltage - 0.5) * 100 ;
  //float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

  Serial.println(celsius); 
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();
    if (command.equals("red")) {
      leds[0]=CRGB(255, 0, 0);
      FastLED.show();
      delay(500); 

    }

    else if (command.equals("blue")) {
      leds[0]=CRGB(0, 0, 255);
      FastLED.show();
      delay(500);
    }
    
  }

  delay(1000);
}
