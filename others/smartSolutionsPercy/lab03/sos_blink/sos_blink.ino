int ledPin = 2;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // S
  sos_flash(200);
  sos_flash(200);
  sos_flash(200);

  delay(300);

  // O
  sos_flash(500);
  sos_flash(500);
  sos_flash(500);

  // S
  sos_flash(200);
  sos_flash(200);
  sos_flash(200);

  delay(1000);
  
                       
}


void sos_flash(int timing) {
   digitalWrite(ledPin, HIGH);  
   delay(timing);                       
   digitalWrite(ledPin, LOW);   
   delay(timing); 
 }
