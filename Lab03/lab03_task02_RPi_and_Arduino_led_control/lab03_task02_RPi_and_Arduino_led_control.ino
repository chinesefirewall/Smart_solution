//// Include the libraries we need
//#include <SoftwareSerial.h>
//
//String led_state; 
//bool is_led_on = false;
//int pin = 11;
//
//
//SoftwareSerial mySerial(2,3);//(3,4); OR (0,1); //rx, tx
//
//void setup() {
//  mySerial.begin(9600);
//    Serial.begin(9600);
//
//  pinMode(pin, OUTPUT);
//  //mySerial.println("START HUJNU ");
//}
//
//void loop() {
//  //mySerial.listen(); // -----> ADDED
//  //Serial.listen();
//  
//  if (mySerial.available() > 0){
//    led_state = mySerial.readString(); //mySerial.read(); or received_msg = mySerial.readStringUntil('\n');
//    //mySerial.print(led_state);
//    Serial.println(led_state);
//    //mySerial.println();
//    
//    if (led_state == "ON" ) {
//      if (is_led_on == false) {
//        digitalWrite(pin, HIGH);
//        mySerial.print("LED is on");
//        is_led_on = true;
//      }
//      else {
//        mySerial.print("LED already on");
//      }
//    } else if (led_state == "OFF") {
//      if (is_led_on == true) {
//        digitalWrite(pin, LOW);
//        mySerial.print("LED is off");
//        is_led_on = false;
//      }
//      else {
//        mySerial.print("LED already off");
//      }
//    } 
//    
//   
//  }
//  delay(100);
//}

// GOOD WORKING CODE










//// Include the libraries we need
#include <SoftwareSerial.h>

String led_state; 
bool is_led_on = false;
int pin = 11;


SoftwareSerial mySerial(2,3);//(3,4); OR (0,1); //rx, tx

void setup() {
  mySerial.begin(9600);
    //Serial.begin(9600);

  pinMode(pin, OUTPUT);
  //mySerial.println("START HUJNU ");
}

void loop() {
  //mySerial.listen(); // -----> ADDED
  //Serial.listen();
  
  if (mySerial.available() > 0){
    led_state = mySerial.readString(); //mySerial.read(); or received_msg = mySerial.readStringUntil('\n');
    mySerial.print(led_state);
    //Serial.println(led_state);
    //mySerial.println();
    
    if (led_state == "ON" ) {
      mySerial.print("LED is on");
      if (is_led_on == false) {
        digitalWrite(pin, HIGH);
        //mySerial.print("LED is on");
        is_led_on = true;
      }
      else if (is_led_on = true && led_state == "ON" ){
        mySerial.print("LED already On> ");
      }
    } else if (led_state == "OFF") {
      mySerial.print("LED is off");
      if (is_led_on == true) {
        digitalWrite(pin, LOW);
        //mySerial.print("LED is off");
        is_led_on = false;
      }
      else {
        //mySerial.print("LED already off");
      }
    } 
    
   
  }
  delay(100);
}
