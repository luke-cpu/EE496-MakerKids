#include <RGBmatrixPanel.h>
#include <math.h>

#define CLK  8 
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

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
int j;

void setup() {
  matrix.begin();
  //delay(1000);
  
//  matrix.setTextWrap(false); // Allow text to run off right edge
//  matrix.setTextSize(2);
  Serial.begin(9600);
  
}

void loop() {
  if (Serial.available() > 0) {
    receiverData = Serial.read();
    //receiverData = log(receiverData)/log(2);
    //Serial.print(receiverData);
    //Serial.println(" received");
    switch(receiverData)
    {
      case 2: // 0 
        matrix.fillRect(0, 8, 2, 16, matrix.Color333(1,1,1));
      break;
      case 3: // 1
        matrix.fillRect(2, 8, 2, 16, matrix.Color333(1,1,1));
      break;
      case 5: // 2
        matrix.fillRect(4, 8, 2, 16, matrix.Color333(1,1,1));
      break;
      case 9: // 3
        matrix.fillRect(6, 8, 2, 16, matrix.Color333(1,1,1));
      break;
      case 17: // 4
        matrix.fillRect(8, 8, 2, 16, matrix.Color333(1,1,1));
      break;
      case 33: // 5
        matrix.fillRect(10, 8, 2, 16, matrix.Color333(1,1,1));
      break;
      case 65: // 6
        matrix.fillRect(12, 8, 2, 16, matrix.Color333(1,1,1));
      break;
      case 129: // 7
        matrix.fillRect(14, 8, 2, 16, matrix.Color333(1,1,1));
      break;
      case 257: // 8
        matrix.fillRect(16, 8, 2, 16, matrix.Color333(1,1,1));
      break;
      case 513: // 9
        matrix.fillRect(18, 8, 2, 16, matrix.Color333(1,1,1));
      break;
      case 1025: // 10
        matrix.fillRect(20, 8, 2, 16, matrix.Color333(1,1,1));
      break;
      case 2049: // 11
        matrix.fillRect(22, 8, 2, 16, matrix.Color333(1,1,1));
      break;
      default: matrix.fillScreen(0);
    }
  }
  else
  {

// filRect(x star postion, y start position, +x direction, -y direction, color)
  
  byte i;
  // Clear background
  matrix.fillScreen(0);
  currentState = digitalRead(buttonPin);
  if((currentState == LOW) && (previousState == HIGH)) // If button is depressed
  {
    switch(mode) // Cycle to the next mode
    {
      case 1: mode=2;
        break;
      case 2: mode=3;
        break;
      case 3: mode=1;
        break;
      default: mode=1;
    }
  }
  previousState = currentState;
  delay(debounceDelay);
//  
//  // Draw big scrolly text on top
////  matrix.setTextColor(matrix.ColorHSV(hue, 255, 255, true));
////  matrix.setCursor(textX, 1);
////  switch(mode) // Display the current mode
////  {
////    case 1: matrix.print(F2(mode1Str));
////      break;
////    case 2: matrix.print(F2(mode2Str));
////      break;
////    case 3: matrix.print(F2(mode3Str));
////      break;
////    default: matrix.print(F2(mode1Str));
////  }
//
//  // Move text left (w/wrap), increase hue
//  //if((--textX) < textMin) textX = matrix.width();
//
////#if !defined(__AVR__)
////  // On non-AVR boards, delay slightly so screen updates aren't too quick.
////  delay(20);
////#endif
////
//  // Update display
  //matrix.swapBuffers(false);

  }
  delay(1);
}
