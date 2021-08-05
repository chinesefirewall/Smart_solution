//########################################################################
//        file: bt05-v3-at-master-setup-percom
//     version: 20210408
//      author: Heiki Kasemägi <cipo@ut.ee>
// description: distribution cource code
//
// copyright (c) 2021, Heiki Kasemägi
//
//########################################################################
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA  02110-1301, USA
//
//########################################################################
// Käesolev programm on vaba tarkvara. Te võite seda edasi levitada ja/või
// muuta vastavalt GNU Üldise Avaliku Litsentsi tingimustele, nagu need on
// Vaba Tarkvara Fondi poolt avaldatud; kas Litsentsi versioon number 2
// või (vastavalt Teie valikule) ükskõik milline hilisem versioon.
//
// Seda programmi levitatakse lootuses, et see on kasulik, kuid ILMA
// IGASUGUSE GARANTIITA; isegi KESKMISE/TAVALISE KVALITEEDI GARANTIITA või
// SOBIVUSELE TEATUD KINDLAKS EESMÄRGIKS. Üksikasjade suhtes vaata GNU
// Üldist Avalikku Litsentsi.
//
// Te peaks olema saanud GNU Üldise Avaliku Litsentsi koopia koos selle
// programmiga, kui ei, siis kontakteeruge Free Software Foundation'iga,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
//
//########################################################################

// Bluetooth HC-05 v3.0-20170601 AT master config and communication code
//
// for Arduino Nano
// use software serial on pins D3, D2 (rx,tx resp.) via level shifter
// use D4 for EN-pin
// use D13 for VCC-pin
//
// note that there should be the response in the serial monitor after each command
// issued via "atcommand"...if not, something is wrong....

#include <SoftwareSerial.h>

SoftwareSerial bt(3, 2); // rx,tx
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
// specify slave address in two formats:
// xxxx:yy:zzzzzz
// to find the slave address, scan the network and add the address in its excact format as
// found form the network...samples are below
String BTSlave = "0021:13:00BFA2";
//String BTSlave="3C71:BF:44784"; // ESP32:1
//String BTSlave="98D3:31:FD3675,1F00,7FFF"; // B11
//String BTSlave="98D3:31:FB37E5,1F00,7FFF"; // B7

// this is the real MAC for actual connection
// xxxx,yy,zzzzzz
String BTSlaveC = "0021,13,00BFA2"; //
//String BTSlaveC="98D3,31,FD3675"; // B11
//String BTSlaveC="98D3,31,FB37E5"; // B7


int VCCpin = 4;
int ENpin = 5;

String masterName = "hc05v3-28";

String inputString, outputString;

void setup() {
  // EN pin
  pinMode(ENpin, OUTPUT);
  // VCC pin
  pinMode(VCCpin, OUTPUT);
  // poweroff module
  digitalWrite(VCCpin, LOW);

  Serial.begin(9600);
  // BT AT mode goes at 38400 baud
  bt.begin(38400);
  // set EN HIGH
  digitalWrite(ENpin, HIGH);
  // power the module
  delay(5000);
  digitalWrite(VCCpin, HIGH);

  Serial.println("== initialising HC-05v3.0-20170601 BT module as master...==");
  lcd.init();// initialize the lcd
  lcd.backlight();// Backlight ON
  lcd.setCursor(1, 0); // 2nd column,1st row
  lcd.print("Hello!");
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
  Serial.println("== set EN low ==");
  digitalWrite(ENpin, LOW);
  atcommand("AT+CMODE=0\r\n"); // allow to connect only specific slave
  atcommand("AT+INQM=0,5,9\r\n");
  //atcommand("AT+INIT\r\n");

  Serial.println("== power off ==");
  digitalWrite(VCCpin, LOW);
  delay(1000);
  Serial.println("== power on ==");
  digitalWrite(VCCpin, HIGH);

  bt.begin(9600);
  delay(2000);

  //atcommand("AT+STATE\r\n");
  //delay(2000);

  

  

}

void loop() {
  // put your main code here, to run repeatedly:
  // the following code sends string "send" to ask the
  // slave to excecute the command built into the slave
  lcd.init();// initialize the lcd
  lcd.backlight();// Backlight ON
  lcd.setCursor(1, 0); // 2nd column,1st row
  lcd.print(bt.readString());

  delay(2000); // set delay long enough to enable the slave to process the request and answer
}


void atcommand(const String _atcommand)
{
  Serial.print("== ");
  Serial.print(_atcommand);
  bt.print(_atcommand);
  delay(1000);
  while (bt.available())
    Serial.write(bt.read());

  //return 0;
};

bool find_address(const String _raddr)
{

  bool status = false;
  String seadmed;
  int firstIndex, lastIndex;
  //  int i=0;

  Serial.print("== AT+INQ\r\n");
  bt.print("AT+INQ\r\n");
  delay(9000);
  while (bt.available())
  {
    seadmed = bt.readString();
  }

  Serial.println(seadmed);

  if (seadmed.indexOf(_raddr) > -1)
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
