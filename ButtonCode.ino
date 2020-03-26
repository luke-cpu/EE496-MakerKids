// Pin variables
int buttonPin = 2;

// State variables
int currentState;
int previousState = LOW;

// Debounce variables
int debounceDelay = 100;

// Mode variables
int mode = 1;

void setup() {
  pinMode(buttonPin, INPUT);
  //Serial.begin(9600);
}

// Change mode with button
void loop() {
  currentState = digitalRead(buttonPin);

  if((currentState == LOW) && (previousState == HIGH)) // If button is depressed
  {
    switch(mode)
    {
      case 1: mode = 2;
        break;
      case 2: mode = 3;
        break;
      case 3: mode = 4;
        break;
      case 4: mode = 1;
        break;
      default: mode = 1;
    }
  }
  previousState = currentState;
  
  //Serial.print(mode);
  //Serial.print(F("\n"));
  
  delay(debounceDelay);
}
