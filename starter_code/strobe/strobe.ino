/*
* Essentials of PCB Design
* Flashlight: Turns on all LEDs to white at full brightness
* This is very bright and will use a lot of current!
*
* Track 1 boards compile for Arduino Leonardo
* Requirements:
* - FastLED library
*/

#include <FastLED.h>

// You may need to change these for your board
#define NUM_LEDS 27
#define DATA_PIN 5

// Array of LEDs
CRGB leds[NUM_LEDS];

// Setup function - runs once at the start
void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

// Loop function - repeatedly called after setup()
void loop() {
  FastLED.showColor(CRGB(255, 255, 255), 255);
  FastLED.show();
  delay(50);
  FastLED.clear();
  delay(50);
}
