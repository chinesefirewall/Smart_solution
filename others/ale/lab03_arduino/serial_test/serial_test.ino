String s;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    s = Serial.readString();
    Serial.print(s);
  }
}

