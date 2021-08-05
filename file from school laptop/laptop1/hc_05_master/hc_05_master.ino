//hc-05
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

SoftwareSerial mySerial(3, 2); //Rx,Tx

String recv;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Hello");
  
  mySerial.begin(9600);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);

  lcd.init();// initialize the lcd
  lcd.backlight();// Backlight ON
  lcd.setCursor(1, 0); // 2nd column,1st row
  lcd.print("Hello!");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mySerial.available()){
    if(mySerial.readString() == "tere"){
      recv = mySerial.readString();
    
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(recv);
    
      Serial.println(recv);
      delay(50);
    }
  }
}
