#include <SoftwareSerial.h>
#include <U8g2lib.h>
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 
SoftwareSerial mySerial(3,2);
String message; //Message buffer
void setup() {
  Serial.begin(9600);
  u8g2.begin();
  mySerial.begin(9600);
}

void loop() {
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2.drawStr(8,29,"...");  // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
  
  while (mySerial.available()) {
    message = mySerial.readString();
    mySerial.print(message); //display message and
    Serial.print(message); //display message and
    //message = message.substring(0,8);
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2.drawStr(8,29,message.c_str());  // write something to the internal memory
    u8g2.sendBuffer();          // transfer internal memory to the display
    message = ""; //clear buffer
    delay(5000);
  }
}
