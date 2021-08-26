#include <SoftwareSerial.h>

SoftwareSerial bt(3, 2); // rx,tx
int counter = 0;
String inputString, outputString;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("== initialising HC-05 BT module as slave...==");
  // switch to BT comunication mode at 9600 baud
  bt.begin(9600);
  Serial.println("== entering into the communication mode...the table is yours ;)...==");

}


void loop() {
  // put your main code here, to run repeatedly:
  if (bt.available())
  {
    inputString = bt.readString();
    delay(500); // set the delay long enough to read in the entire incoming buffer
    Serial.println(inputString); 
    if (inputString == "send"); // master is expected to send this keyword
    {
      Serial.print("== sending: ");
      Serial.println(counter);
      bt.print(counter);
      counter++;
    }
  }
  if (Serial.available())
  {
    outputString = Serial.readString();
    Serial.print("== local: ");
    //  /Serial.println(outputString);
    bt.print(outputString);
  }
}
