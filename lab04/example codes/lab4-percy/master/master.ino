void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial Monitor Connected");

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()) {
    Serial.println(Serial.read());
    delay(1000);
   }
  
}
