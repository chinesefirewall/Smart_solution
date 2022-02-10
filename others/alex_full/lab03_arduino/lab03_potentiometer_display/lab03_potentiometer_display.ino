
#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

int analog_pin;
float volt;
String volt_s;
// For rescaling angle to voltage
float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  u8x8.begin();
  u8x8.setPowerSave(0);
  
  // welcome message
  delay(2000);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.print("Welcome bro");
  delay(2000);
  u8x8.clear();
  
}

void loop() {
  // put your main code here, to run repeatedly:
    
  // read from analog
  analog_pin = analogRead(A0);
  // angle to voltage
  volt = floatMap(analog_pin, 0, 1023, 0, 5);
  volt_s = String(volt, 2);
  Serial.print(volt);
  //Serial.print(" --> ");
  //Serial.println(volt_s);
  
  //Display
  u8x8.print(volt_s);
  delay(1000);
  u8x8.clear();
}
