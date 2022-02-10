
String s;
bool is_led_on = false;

void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  //Serial.println("START HUJNU ");
}

void loop() {
  if (Serial.available() > 0){
    s = Serial.readString();
    //Serial.println(s);
    
    if (s == "ON") {
      if (is_led_on == false) {
        digitalWrite(12, HIGH);
        Serial.print("LED is on");
        is_led_on = true;
      }
      else {
        Serial.print("LED already on");
      }
    } else if (s == "OFF") {
      if (is_led_on == true) {
        digitalWrite(12, LOW);
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
