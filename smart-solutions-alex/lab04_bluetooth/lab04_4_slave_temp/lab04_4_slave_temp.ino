//########################################################################
//        file: bt05-at-slave-setup-percom
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

// Bluetooth HC-05 v2-20100601 and v3-20170601 AT master config and communication code
//
// for Arduino Nano
// use software serial on pins D3, D2 (rx,tx resp.) via level shifter
// use D4 for EN-pin
// use D13 for VCC-pin
//
// note that there should be the response in the serial monitor after each command
// issued via "atcommand"...if not, something is wrong....
// Bluetooth AT slave config and communication code
//
// for Arduino Nano
// use software serial on pins D3, D2 (rx,tx resp.) via level shifter
// use D4 for EN-pin
// use D13 for VCC-pin
//
// in the communication part, the slave sends the value of the counter and then
// increments the counter...keyword is "send"
// the communication through the serial monitor works too...
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

float temp_c;
String temp_s;
SoftwareSerial bt(2 ,3); // rx,tx

String slaveName="np-05-05";

int counter = 0;
String inputString, outputString;

void setup() {
  sensors.begin();  // Start up the library
  Serial.begin(9600);
// BT AT mode goes at 38400 baud
  bt.begin(38400);


Serial.println("== initialising HC-05 BT module as slave...==");

// initiate module as slave

atcommand("AT\r\n");
atcommand("AT\r\n");
atcommand("AT\r\n");
atcommand("AT+ORGL\r\n");
//atcommand("AT+RMAAD\r\n");
atcommand("AT+NAME="+slaveName+"\r\n");
atcommand("AT+ADDR?\r\n");
atcommand("AT+UART=9600,0,0\r\n");
atcommand("AT+PSWD?\r\n");
atcommand("AT+ROLE=0\r\n");
atcommand("AT+RESET\r\n");
atcommand("AT+CMODE=1\r\n");

// set EN LOW
  //digitalWrite(ENpin,LOW);
  delay(1000);

// poweroff module
  //digitalWrite(VCCpin,LOW);
  //delay(1000);
// power the module in communication mode
  //digitalWrite(VCCpin,HIGH);
  //delay(1000);

// switch to BT comunication mode at 9600 baud
  bt.begin(9600);
  Serial.println("== entering into the communication mode...the table is yours ;)...==");

}

void loop() {
  // put your main code here, to run repeatedly:

  if (bt.available() > 0)
  {
    inputString = bt.readString();
    delay(500); // set the delay long enough to read in the entire incoming buffer
    Serial.println(inputString);
    if(inputString=="send"); // master is expected to send this keyword
    {
      Serial.print("== sending: ");
      sensors.requestTemperatures(); 
      temp_c = sensors.getTempCByIndex(0);
      temp_s = String(temp_c, 2);
      Serial.println(temp_s);
      bt.print(temp_s);
      //counter++;
    }
  }
  /*
if(Serial.available())
{
  outputString = Serial.readString();
  Serial.print("== local: ");
  Serial.println(outputString);
  bt.print(outputString);
}
*/
}


void atcommand(const String _atcommand)
{
  Serial.print("== ");
  Serial.print(_atcommand);
  bt.print(_atcommand);
  delay(1000);
  while(bt.available())
    Serial.write(bt.read());

return 0;
}
