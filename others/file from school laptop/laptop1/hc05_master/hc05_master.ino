// Bluetooth AT master config and communication code
//
// for Arduino Nano
// use software serial on pins D2. D3 (rx,tx resp.) via level shifter
// use D4 for EN-pin via level shifter
// use D5 for VCC-pin

#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
//I2C LCD is connected directly to Arduino, SCL is conneted to A5, SDA to A4, VCC is connected to 5V

SoftwareSerial bt(2, 3); // rx,tx

// specify slave address in two formats:
// xxxx:yy:zzzzzz
String BTSlave = "98D3:31:FD2025,1F00,7FFF";
// xxxx,yy,zzzzzz
String BTSlaveC = "98D3,31,FD2025";

int VCCpin = 9;
int ENpin = 7;
String recv;

String masterName = "np-05-07";

void setup() {
  // EN pin
  pinMode(ENpin, OUTPUT);
  // VCC pin
  pinMode(VCCpin, OUTPUT);
  // poweroff module
  digitalWrite(VCCpin, LOW);
//  digitalWrite(ENpin,LOW);

  Serial.begin(9600);
  // BT AT mode goes at 38400 baud
  bt.begin(38400);
  // set EN HIGH
  digitalWrite(ENpin, HIGH);
  delay(1000);
  // power the module
  digitalWrite(VCCpin, HIGH);

  Serial.println("initialising HC-05 BT module as master...");

  // initiate module as master

  atcommand("AT\r\n");
  atcommand("AT\r\n");
  atcommand("AT\r\n");
  atcommand("AT+ORGL\r\n");
  atcommand("AT+RMAAD\r\n");
  atcommand("AT+NAME=" + masterName + "\r\n");
  atcommand("AT+ADDR?\r\n");
  atcommand("AT+UART=9600,0,0\r\n");
  atcommand("AT+PSWD?\r\n");
  atcommand("AT+ROLE=1\r\n");
  atcommand("AT+RESET\r\n");
  atcommand("AT+CMODE=0\r\n");
  atcommand("AT+INQM=0,5,9\r\n");
  atcommand("AT+INIT\r\n");

  while (!find_address(BTSlave))
  {
    Serial.println("not found...trying again in 5 s...");
    delay(5000);
  }

  Serial.println("device found...pairing...");

  atcommand("AT+PAIR=" + BTSlaveC + ",9\r\n");
  atcommand("AT+BIND=" + BTSlaveC + "\r\n");
  atcommand("AT+CMODE=0\r\n");
  atcommand("AT+LINK=" + BTSlaveC + "\r\n");

  Serial.println("connected to " + BTSlave + "...entering the communication mode...2 quick flashes indicate the connection...the table is yours...");
delay(2000);
  //// set EN LOW to enter communication mode
  digitalWrite(ENpin, LOW);
  delay(5000);
  bt.println("hello");
  Serial.println("trying to send 'hello' to slave...if responce is 'ERROR(0)', please reboot the slave...");
  lcd.init();// initialize the lcd
  lcd.backlight();// Backlight ON
  lcd.setCursor(1, 0); // 2nd column,1st row
  lcd.print("Hello!");
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  bt.print("temp");
  if (bt.available()) {
    delay(1000);
    recv = bt.readString();
    Serial.println(recv);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print ("Temperature is:");
    lcd.setCursor(0, 1);
    lcd.print(recv);

//    Serial.write(bt.read());
  }
  if (Serial.available())
  {
    bt.println(Serial.readString());

  }
  delay(2000);
}


void atcommand(const String _atcommand)
{
  Serial.print(_atcommand);
  bt.print(_atcommand);
  delay(1000);
  while (bt.available())
    Serial.write(bt.read());

  return 0;
};

bool find_address(const String _raddr)
{

  bool status = false;
  String seadmed;
  int firstIndex, lastIndex;
  //  int i=0;

  Serial.print("AT+INQ\r\n");
  bt.print("AT+INQ\r\n");
  delay(1000);
  while (bt.available())
  {
    seadmed = bt.readString();
  }

  Serial.println(seadmed);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(seadmed);
  delay(50);
  if (seadmed.indexOf(_raddr) > -1)
  {
    //    firstIndex=seadmed.indexOf(_raddr);
    //    lastIndex=seadmed.lastIndexOf(_raddr);
    //    Serial.println(firstIndex);
    //    Serial.println(lastIndex);
    //    Serial.println(seadmed.substring(firstIndex,firstIndex+14));
  }
  return true;

};
