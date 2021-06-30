// unit of time
int time_unit = 200; //milli seconds

int led_pin = 11; // pin to light on arduino

// SOS standard timing- 3 fast flashes and 3 long flashes

void setup() {
  //  setup code:
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  // main code to run repeatedly  in nloop:

  // FAST
  digitalWrite(led_pin, HIGH);
  delay(time_unit);
  digitalWrite(led_pin, LOW);

  // between simbols
  delay(time_unit);

  // FAST
  digitalWrite(led_pin, HIGH);
  delay(time_unit);
  digitalWrite(led_pin, LOW);

  // between simbols
  delay(time_unit);

  // FAST
  digitalWrite(led_pin, HIGH);
  delay(time_unit);
  digitalWrite(led_pin, LOW);

  // between letters (S)
  delay(3*time_unit);

  // SLOW
  digitalWrite(led_pin, HIGH);
  delay(3*time_unit);
  digitalWrite(led_pin, LOW);

  // between simbols
  delay(time_unit);

  // SLOW
  digitalWrite(led_pin, HIGH);
  delay(3*time_unit);
  digitalWrite(led_pin, LOW);

  // between simbols
  delay(time_unit);

  // SLOW
  digitalWrite(led_pin, HIGH);
  delay(3*time_unit);
  digitalWrite(led_pin, LOW);

  // between letters (O)
  delay(3*time_unit);

  // FAST
  digitalWrite(led_pin, HIGH);
  delay(time_unit);
  digitalWrite(led_pin, LOW);

  // between simbols
  delay(time_unit);

  // FAST
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
