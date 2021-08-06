
// code sample source: https://www.arduino.cc/en/tutorial/potentiometer and https://tronixstuff.com/2019/08/29/ssd1306-arduino-tutorial/

#include <SoftwareSerial.h>
#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

SoftwareSerial mySerial(2,3);//(3,4); OR (0,1); //rx, tx
int analog_pin;
float volt;
String volt_s;
// For rescaling angle to voltage
float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  u8x8.begin();
  u8x8.setPowerSave(0);
  
  // welcome screen
  delay(1000);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.print("Welcome to the potentiometer problem bro");
  delay(1000);
  u8x8.clear();
  
}

void loop() {
  // put your main code here, to run repeatedly:
    
  // read from analog  and do the potentiometer thingy
  analog_pin = analogRead(A0);
  // angle to voltage
  volt = floatMap(analog_pin, 0, 1023, 0, 5); //map 0:1023 to btw 0 and 5
  volt_s = String(volt, 2);
  mySerial.print(volt);
  //mySerial.print(" --> ");
    mySerial.println(volt_s);
  
  //Displaying the voltage
  u8x8.print(volt_s);
  delay(1000);
  u8x8.clear();
}
