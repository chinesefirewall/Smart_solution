
#include <IRremote.h>

IRsend irsend;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
irsend.sendNEC(0xFF10EF, 32);
delay(2000);
}
