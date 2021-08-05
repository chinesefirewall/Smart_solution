// Include the libraries we need
#include <SoftwareSerial.h>

String led_state; 
bool is_led_on = false;
int pin = 11;


SoftwareSerial mySerial(0,1);//(3,4); OR (0,1); //rx, tx

void setup() {
  mySerial.begin(9600);
  pinMode(pin, OUTPUT);
  //mySerial.println("START HUJNU ");
}

void loop() {
  //mySerial.listen();
  
  if (mySerial.available() > 0){
    led_state = mySerial.readStringUntil('\n'); //mySerial.read(); or received_msg = mySerial.readStringUntil('\n');
    mySerial.println();
    
    if (led_state == "ON" ) {
      if (is_led_on == false) {
        digitalWrite(pin, HIGH);
        mySerial.print("LED is on");
        is_led_on = true;
      }
      else {
        mySerial.print("LED already on");
      }
    } else if (led_state == "OFF") {
      if (is_led_on == true) {
        digitalWrite(pin, LOW);
        mySerial.print("LED is off");
        is_led_on = false;
      }
      else {
        mySerial.print("LED already off");
      }
    } 
    
   
  }
  delay(100);
}
