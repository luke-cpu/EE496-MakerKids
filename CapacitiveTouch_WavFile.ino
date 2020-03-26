//===Maker Kids 3.26.20 - SD card breakout .wav files working with Capactive touch inputs===//

//This iteration currently has a .wav file play from the SD Card directly upon startup.
//The capacitive touch sensor works alongside the sd card reader, but it has proven difficult 
//  to get an outputted .wav file to play upon a specific capacitive touch being inputted.
//It seems that the .wav file will loop with the clock cycle when a touch is pressed because
//  it is extremely fast.
//Maybe there is a way to toggle a variable when an input has been touched?



//***SD CARD INITIALIZATIONS***//
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h" // SD Card libraries
#define SD_ChipSelectPin 10 // Where CS of SD Card breakout is connected
TMRpcm tmrpcm;


//***CAPACITIVE TOUCH INITIALIZATIONS***//
#include <Wire.h>
#include "Adafruit_MPR121.h" // Capacitive touch libraries

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();
uint16_t lasttouched = 0;
uint16_t currtouched = 0;



void setup(){
//***SD CARD SETUP***//
  Serial.begin(9600);
  tmrpcm.speakerPin=9;
  if(!SD.begin(SD_ChipSelectPin)){ // Checks if SD Card breakout is connected to the CS pin correctly
    Serial.println("SD fail");
    return;
  }
  tmrpcm.setVolume(3); // Sets volume of speaker *goes up to 10, but 6 is max for our set up*
  //tmrpcm.play("test.wav"); // A test wav file currently in the sd card; not connected to a capacitive touch and plays upon startup
  while (!Serial) { // needed to keep Arduino from starting up too fast
    delay(100);
  }

//***CAPACITIVE TOUCH SETUP***//
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
}



void loop() {
  // put your main code here, to run repeatedly:
  
  currtouched = cap.touched();
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
      if(i == 5){
        tmrpcm.play("test.wav")
      }
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
      tmrpcm.stopPlayback();
    }
  }

  // reset our state
  lasttouched = currtouched;

  // comment out this line for detailed data from the sensor!
  return;
  
  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
  
  // put a delay so it isn't overwhelming
  delay(100);
}
