#include <IRremote.h>

const int sendpin = 3;
IRsend sender;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("sending zero");
  //sending on
  sender.sendNEC(0xFF30CF, 32);
  delay(1000);
  // Sending off
  sender.sendNEC(0xFFA857, 32);
  delay(600);
}
