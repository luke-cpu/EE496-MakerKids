#include <RGBmatrixPanel.h>

#define CLK  8 
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);

// Similar to F(), but for PROGMEM string pointers rather than literals
#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

//const char str[] PROGMEM = "Mode 1";
const char mode1Str[] PROGMEM = "Mode 1";
const char mode2Str[] PROGMEM = "Mode 2";
const char mode3Str[] PROGMEM = "Mode 3";
const char mode4Str[] PROGMEM = "Mode 4";
int16_t    textX         = matrix.width(),
           textMin       = sizeof(mode1Str) * -12,
           hue           = 0;

// Pin variables
int buttonPin = 11;

// State variables
int currentState;
int previousState = LOW;

// Debounce variables
int debounceDelay = 10;

// Mode variables
int previousMode;
int mode = 1;

int receiverData;

void setup() {
  matrix.begin();
  matrix.setTextWrap(false); // Allow text to run off right edge
  matrix.setTextSize(2);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    receiverData = Serial.read();
    Serial.print(receiverData);
    Serial.println(" received");
  }
  
  byte i;
  // Clear background
  matrix.fillScreen(0);
  currentState = digitalRead(buttonPin);
  if((currentState == LOW) && (previousState == HIGH)) // If button is depressed
  {
    switch(mode) // Cycle to the next mode
    {
      case 1: mode=2; //Serial.println(mode);
        break;
      case 2: mode=3; //Serial.println(mode);
        break;
      case 3: mode=1; //Serial.println(mode);
        break;
      default: mode=1; //Serial.println(mode);
    }
  }
  previousState = currentState;
  delay(debounceDelay);
  
  // Draw big scrolly text on top
  matrix.setTextColor(matrix.ColorHSV(hue, 255, 255, true));
  matrix.setCursor(textX, 1);
  switch(mode) // Display the current mode
  {
    case 1: matrix.print(F2(mode1Str));
      break;
    case 2: matrix.print(F2(mode2Str));
      break;
    case 3: matrix.print(F2(mode3Str));
      break;
    default: matrix.print(F2(mode1Str));
  }

  // Move text left (w/wrap), increase hue
  if((--textX) < textMin) textX = matrix.width();

#if !defined(__AVR__)
  // On non-AVR boards, delay slightly so screen updates aren't too quick.
  delay(20);
#endif

  // Update display
  matrix.swapBuffers(false);
}
