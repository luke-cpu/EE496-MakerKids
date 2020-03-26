#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "pitches.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

int scale [] = {NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6};

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

void setup() {
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  
  //Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  //Serial.println("MPR121 found!");
}

void loop() {
  currentState = digitalRead(buttonPin);
  if((currentState == LOW) && (previousState == HIGH)) // If button is depressed
  {
    switch(mode) // Cycle to the next mode
    {
      case 1: mode=2; Serial.println(mode);
        break;
      case 2: mode=3; Serial.println(mode);
        break;
      case 3: mode=4; Serial.println(mode);
        break;
      case 4: mode=1; Serial.println(mode);
        break;
      default: mode=1; Serial.println(mode);
    }
  }
  previousState = currentState;
  delay(debounceDelay);
  
  // Get the currently touched pads
  currtouched = cap.touched();
  switch(mode){
    case 1:
      for (uint8_t i=0; i<12; i++) {
        // it if *is* touched and *wasnt* touched before, alert!
        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
          //Serial.print(i); Serial.println(" touched");
          //Serial.write(i);
          tone(3, scale[i]); //360*.95
        }
        // if it *was* touched and now *isnt*, alert!
        if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
          //Serial.print(i); Serial.println(" released");

          noTone(3);
        }
      }
      break;
    case 2:
      for (uint8_t i=0; i<12; i++) {
        // it if *is* touched and *wasnt* touched before, alert!
        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
          //Serial.print(i); Serial.println(" touched");
          //Serial.write(i);
          tone(3, scale[11-i]); //360*.95
        }
        // if it *was* touched and now *isnt*, alert!
        if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
          //Serial.print(i); Serial.println(" released");

          noTone(3);
        }
      }
      break;
  }

  // reset our state
  lasttouched = currtouched;
}
