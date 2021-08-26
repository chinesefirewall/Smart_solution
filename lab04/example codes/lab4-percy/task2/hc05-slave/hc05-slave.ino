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
//#include <Adafruit_RGBLCDShield.h>
//#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

SoftwareSerial bt(2,3); // rx,tx
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int ENpin=4;
int VCCpin=5;

String slave_name="np-05-04";
String received_msg = "";


void setup() {
  // DISPLAY INITIALIZATION
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("start");
  
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
  
}

void loop() {
  // put your main code here, to run repeatedly:
if(bt.available())
{
  
  // from bluetooth to Terminal
  //Serial.println(bt.readStringUntil('\n'));
  //received_msg = bt.readStringUntil('\n');

  // Display the message on LED
  lcd.clear();
  lcd.setCursor(3,0); 
  lcd.print(bt.readStringUntil('\n'));
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
