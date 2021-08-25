/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 12;
const int LEDPIN = 8;

IRrecv irrecv(RECV_PIN);

decode_results results;


void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin"); 

  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    if (results.value == 0x9716BE3F) {
        Serial.println("Led ON");
        digitalWrite(LEDPIN, HIGH);
      }

    if (results.value == 0xC101E57B) {
        Serial.println("Led OFF");
        digitalWrite(LEDPIN, LOW);
      }

    Serial.print(", bits: ");
    Serial.println(results.bits);
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
