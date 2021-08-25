/* adapted from https://create.arduino.cc/projecthub/Raushancpr/arduino-with-ir-sensor-1579b6
 *  by adebayo niyi
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 12;
const int LEDPIN = 8;

IRrecv irrecv(RECV_PIN);

decode_results results;


void setup()
{

/*
 {  pinMode (IRSensor, INPUT); // sensor pin INPUT
  pinMode (LED, OUTPUT); // Led pin OUTPUT
}
 * 
 */
  
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("[INFO] Enabling IR-in");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin"); 

  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
//for task 1 use tis code for OFF signal:  0x9716BE3F
// for task 2 use tis code for OFF signal:  0xB91A396A
    if (results.value == 0xB91A396A) {
        Serial.println("[INFO] Led ON");
        digitalWrite(LEDPIN, HIGH);
      }
//for task 2 use tis code for OFF signal:    0xC101E57B
// //for task 2 use tis code for OFF signal:    0x4239449C
    if (results.value == 0x4239449C) {
        Serial.println("[INFO] Led OFF");
        digitalWrite(LEDPIN, LOW);
      }

    Serial.print(", bits: ");
    Serial.println(results.bits);
    irrecv.resume(); // Receive the next value
  }
  delay(200);
}
