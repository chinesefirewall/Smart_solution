// Bluetooth HC-05 v3.0-20170601 AT master config and communication code
//
// for Arduino Nano
// use software serial on pins D2. D3 (rx,tx resp.) via level shifter
// use D4 for EN-pin via level shifter
// use D5 for VCC-pin
// use A

#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

SoftwareSerial bt(2,3); // rx,tx
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// specify slave address in two formats:
// xxxx:yy:zzzzzz
String BTSlave="0013:EF:0083B5";
String BTSlaveC="0013,EF,0083B5";

//Defining PINs
int VCCpin=5;
int ENpin=4;

String masterName="MASTER-CONTROL";
String messagein;

void setup() {
  // DISPLAY INITIALIZATION
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Initialization");
  
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
  
  Serial.println("initialising HC-05v3.0-20179691 BT module as master...");
  
  // initiate module as master
  
  atcommand("AT\r\n");
  atcommand("AT\r\n");
  atcommand("AT\r\n");
  atcommand("AT+ORGL\r\n");
  atcommand("AT+RMAAD\r\n");
  atcommand("AT+NAME="+masterName+"\r\n");
  atcommand("AT+ADDR?\r\n");
  atcommand("AT+UART=9600,0,0\r\n");
  atcommand("AT+PSWD?\r\n");
  atcommand("AT+ROLE=1\r\n");
  atcommand("AT+RESET\r\n");
  Serial.println("set EN low");
  digitalWrite(ENpin,LOW);
  atcommand("AT+CMODE=0\r\n");
  atcommand("AT+INQM=0,5,9\r\n");
  //atcommand("AT+INIT\r\n");
  
  Serial.println("power off");
  digitalWrite(VCCpin,LOW);
  delay(1000);
  Serial.println("power on");
  digitalWrite(VCCpin,HIGH);
  
  bt.begin(9600);
  delay(2000);
  
  //atcommand("AT+STATE\r\n");
  //delay(2000);
  
  while(!find_address(BTSlave))
  {
    Serial.println("not found...trying again in 5 s...");
    delay(5000);
  }
  
  Serial.println("device found...pairing...");
  
  atcommand("AT+PAIR="+BTSlaveC+",9\r\n");
  atcommand("AT+BIND="+BTSlaveC+"\r\n");
  atcommand("AT+CMODE=0\r\n");
  atcommand("AT+LINK="+BTSlaveC+"\r\n");
  
  Serial.println("connected to "+BTSlave);
  
  
  //atcommand("AT+RESET\r\n");
  
  Serial.println("power off");
  digitalWrite(VCCpin,LOW);
  delay(2000);
  Serial.println("power on");
  digitalWrite(VCCpin,HIGH);
  Serial.println("...entering the communication mode...2 quick flashes indicate the connection...the table is yours...");
  
  //// set EN LOW to enter communication mode
  //digitalWrite(ENpin,LOW);
  delay(10000);
  bt.println("hello");
  Serial.println("trying to send 'hello' to slave...if responce is 'ERROR(0)', please reboot the slave...");

}

void loop() {
  // put your main code here, to run repeatedly:
if(bt.available())
{ 

  // Displays on LED
  lcd.clear();
  lcd.setCursor(0,0); 
  // read and display message
  lcd.print(bt.readStringUntil('\n'));
  Serial.write(bt.read());
}

// sends what is written in serial to slave
if(Serial.available())
{
  bt.write(Serial.read());
}
}


void atcommand(const String _atcommand)
{
  Serial.print(_atcommand);
  bt.print(_atcommand);
  delay(1000);
    while(bt.available())
    Serial.write(bt.read());
};

bool find_address(const String _raddr)
{

  bool status=false;
  String seadmed;
  int firstIndex,lastIndex;
//  int i=0;
 
  Serial.print("AT+INQ\r\n");
  bt.print("AT+INQ\r\n");
  delay(9000);
  while(bt.available())
  {
    seadmed=bt.readString();   
  }

  Serial.println(seadmed);

  if(seadmed.indexOf(_raddr) > -1)
// {
//    firstIndex=seadmed.indexOf(_raddr);
//    lastIndex=seadmed.lastIndexOf(_raddr);
//    Serial.println(firstIndex);
//    Serial.println(lastIndex);
//    Serial.println(seadmed.substring(firstIndex,firstIndex+14));
//  }
  return true;
  else
    return false;

};
