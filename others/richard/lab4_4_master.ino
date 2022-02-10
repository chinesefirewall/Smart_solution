int nr = 0;
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial bt(2,3); // rx,tx

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino for HC-05 AT mode...waiting...");
  bt.begin(38400);
  Serial.println("BTserial waiting...");
  
  lcd.init(); 
  lcd.backlight();
}

void loop() {
if(bt.available())

{
  //Serial.write(bt.read());
}
  
 if(Serial.available())
 {

 bt.write(Serial.read());
 bt.write(1);
}
nr=nr+1;
if (nr ==7)
{
lcd.clear();
nr = 0;
}
delay(300);
lcd.write(bt.read());
delay(300);
}
