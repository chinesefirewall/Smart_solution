// code adapted from  https://osoyoo.com/2018/08/29/arduino-lesson-ir-remote-receiver-module-and-controller/
#include <IRremote.h>  // use the IRRemote.h


const int irReceiverPin = 2;  //the SIG of receiver module attach to pin2
IRrecv irrecv(irReceiverPin); //Creates a variable of type IRrecv
decode_results results;    // define results

const int ledpin = 8;
String res;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);    //initialize serial,baudrate is 9600
  irrecv.enableIRIn();   // enable ir receiver module

  pinMode(ledpin,OUTPUT);
  digitalWrite(ledpin,LOW);
  
}

void loop() {
  if (irrecv.decode(&results)) //if the ir receiver module receiver data
  {  
    Serial.print("irCode: ");    //print "irCode: "        
    Serial.print(results.value, HEX); //print the value in hexdecimal

    if (results.value == 0xFFA25D){
      Serial.println("on");
      digitalWrite(ledpin,HIGH);
    }
    if (results.value == 0xFF9867){
      Serial.println("off");
      digitalWrite(ledpin,LOW);
    }
     
    Serial.print(",  bits: ");  //print" , bits: "         
    Serial.println(results.bits); //print the bits
    irrecv.resume();    // Receive the next value 
  }  
  delay(600); //delay 600ms

}
