// Bluetooth AT slave config and communication code
//
// for Arduino Nano
// use software serial on pins D2. D3 (rx,tx resp.) via level shifter
// use D4 for EN-pin via level shifter
// use D5 for VCC-pin

#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8X8_SSD1306_128X32_UNIVISION_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED

SoftwareSerial bt(2,3); // rx,tx

int ENpin=4;
int VCCpin=5;

String slave_name="np-05-06";
String received_msg = "";


void setup() {
// EN pin
  pinMode(ENpin,OUTPUT);
// VCC pin
  pinMode(VCCpin,OUTPUT);
// poweroff module
  digitalWrite(VCCpin,LOW);
 
  Serial.begin(9600);
// BT AT mode goes at 38400 baud
  bt.begin(38400);
// set EN HIGH
  digitalWrite(ENpin,HIGH);
  delay(1000);
// power the module
  digitalWrite(VCCpin,HIGH);

Serial.println("initialising HC-05 BT module as slave...");

// initiate module as slave

atcommand("AT\r\n");
atcommand("AT\r\n");
atcommand("AT\r\n");
atcommand("AT+ORGL\r\n");
atcommand("AT+RMAAD\r\n");
atcommand("AT+NAME="+slave_name+"\r\n");
atcommand("AT+ADDR?\r\n");
atcommand("AT+UART=9600,0,0\r\n");
atcommand("AT+PSWD?\r\n");
atcommand("AT+ROLE=0\r\n");
atcommand("AT+RESET\r\n");
atcommand("AT+CMODE=1\r\n");

// set EN LOW
  digitalWrite(ENpin,LOW);
  delay(1000);

// poweroff module
  digitalWrite(VCCpin,LOW);
  delay(1000);
// power the module in communication mode
  digitalWrite(VCCpin,HIGH);
  delay(1000);

// switch to BT comunication mode at 9600 baud
  bt.begin(9600);
  Serial.println("entering into the communication mode...the table is yours ;)...");

  // DISPLAY INITIALIZATION
  /* U8g2 Project: SSD1306 Test Board */
  //pinMode(10, OUTPUT);
  //pinMode(9, OUTPUT);
  //digitalWrite(10, 0);
  //digitalWrite(9, 0);    
  
  /* U8g2 Project: KS0108 Test Board */
  //pinMode(16, OUTPUT);
  //digitalWrite(16, 0);  
  
  u8x8.begin();
  u8x8.setPowerSave(0); 
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,1, "initialization");
  u8x8.refreshDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
if(bt.available())
{
  
  // from bluetooth to Terminal
  Serial.println(bt.readStringUntil('\n'));
  received_msg = bt.readStringUntil('\n');

  //const char *c = received_msg.c_str();
  
  Serial.print("Converted String: ");
  //Serial.println(c);
  
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,1, received_msg.c_str());
  u8x8.refreshDisplay();    // only required for SSD1606/7  
  delay(2000);
}
// from terminal to bluetooth
if(Serial.available())
{
  bt.println(Serial.readString());
  //testscrolltext(received_msg);
}
}


void atcommand(const String _atcommand)
{
  Serial.print(_atcommand);
  bt.print(_atcommand);
  delay(1000);
  while(bt.available())
    Serial.write(bt.read());
}
