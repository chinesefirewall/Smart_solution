// Time unit
int time_unit = 200; //ms

int led_pin = 12;

// SOS standard timing (for myself)
// space (words) 7
// between letters 3
// between simbols (dot, tire) 1
// dot 1
// tire 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // DOT
  digitalWrite(led_pin, HIGH);
  delay(time_unit);
  digitalWrite(led_pin, LOW);

  // between simbols
  delay(time_unit);

  // DOT
  digitalWrite(led_pin, HIGH);
  delay(time_unit);
  digitalWrite(led_pin, LOW);

  // between simbols
  delay(time_unit);

  // DOT
  digitalWrite(led_pin, HIGH);
  delay(time_unit);
  digitalWrite(led_pin, LOW);

  // between letters (S)
  delay(3*time_unit);

  // TIRE
  digitalWrite(led_pin, HIGH);
  delay(3*time_unit);
  digitalWrite(led_pin, LOW);

  // between simbols
  delay(time_unit);

  // TIRE
  digitalWrite(led_pin, HIGH);
  delay(3*time_unit);
  digitalWrite(led_pin, LOW);

  // between simbols
  delay(time_unit);

  // TIRE
  digitalWrite(led_pin, HIGH);
  delay(3*time_unit);
  digitalWrite(led_pin, LOW);

  // between letters (O)
  delay(3*time_unit);

  // DOT
  digitalWrite(led_pin, HIGH);
  delay(time_unit);
  digitalWrite(led_pin, LOW);

  // between simbols
  delay(time_unit);

  // DOT
  digitalWrite(led_pin, HIGH);
  delay(time_unit);
  digitalWrite(led_pin, LOW);

  // between simbols
  delay(time_unit);

  // DOT
  digitalWrite(led_pin, HIGH);
  delay(time_unit);
  digitalWrite(led_pin, LOW);

  // between words (space)
  delay(7*time_unit);
}
