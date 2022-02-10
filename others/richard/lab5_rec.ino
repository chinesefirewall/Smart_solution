
#include <IRremote.h>

#define relay A1
#define interval 1000



int IR = 6;
bool ir = false;
IRrecv irrecv(IR);
decode_results results;
void setup() {
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); 
  irrecv.blink13(true); 
}
void loop()
{

  if (irrecv.decode(&results)) {
   
     Serial.println(results.value,HEX);
     delay(100);
     /////////////////////////
     if(results.value==0xFF10EF)
     {
        ir=!ir;
        digitalWrite(relay, ir);
      
   }
   digitalWrite(relay, ir);
   irrecv.resume();
 
}
delay(10);

}
