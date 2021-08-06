#include <IRremote.h>

const int RECV_PIN = 7;
//Rrecver irrecv;

int relay_pin = 8;
int led_pin = 9;
void setup() {
  pinMode(relay_pin, OUTPUT);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, HIGH);
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN,ENABLE_LED_FEEDBACK);

}
void loop() {
  if (IrReceiver.decode()) {
//    Serial.println(IrReceiver.decodedIRData.decodedRawData);

  //  digitalWrite(relay_pin, HIGH);
  //  delay(3000);
  //  digitalWrite(relay_pin, LOW);
//    irrecv.resume();
IrReceiver.printIRResultRawFormatted(&Serial, true);
   // delay(3000);
   IrReceiver.resume();
  }
}
