
String led_state; 
bool is_led_on = false;
int pin = 18;
void setup() {
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  //Serial.println("START HUJNU ");
}

void loop() {
  if (Serial.available() > 0){
    led_state = Serial.readString();
    //Serial.println();
    
    if (led_state == "ON") {
      if (is_led_on == false) {
        digitalWrite(pin, HIGH);
        Serial.print("LED is on");
        is_led_on = true;
      }
      else {
        Serial.print("LED already on");
      }
    } else if (led_state == "OFF") {
      if (is_led_on == true) {
        digitalWrite(pin, LOW);
        Serial.print("LED is off");
        is_led_on = false;
      }
      else {
        Serial.print("LED already off");
      }
    } 
    
   
  }
  delay(1000);
}
