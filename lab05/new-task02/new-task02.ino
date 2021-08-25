#include <IRremote.h>

const int sendpin = 3;
IRsend sender;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("sending zero ");
  //sending on - button 1 on remote control
  sender.sendNEC(0x9716BE3F, 32);
  Serial.print("sending ON ");
  delay(100);
  // Sending off button 0 on remote
  sender.sendNEC(0xC101E57B, 32);
  Serial.print("sending OFF ");
  delay(600);
}
