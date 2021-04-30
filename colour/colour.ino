// Police light
 
#define WHITEPIN D5
#define GREENPIN D6
#define BLUEPIN D7
#define REDPIN D8
#define YELLOWPIN D1
 
void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(WHITEPIN, OUTPUT);
  pinMode(YELLOWPIN, OUTPUT);
  
  analogWrite(REDPIN, 0);
  analogWrite(BLUEPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(WHITEPIN, 0);
  analogWrite(YELLOWPIN, 0);
          
}

void loop() {
  // Blink 10 times red
  for (int i = 0; i <= 9; i++) {
    analogWrite(REDPIN, 255);
    delay(50);
    analogWrite(REDPIN, 0);
    delay(50);
  }

  // Blink 10 times blue
  for (int i = 0; i <= 9; i++) {
    analogWrite(BLUEPIN, 255);
    delay(50);
    analogWrite(BLUEPIN, 0);
    delay(50);
  }

}
