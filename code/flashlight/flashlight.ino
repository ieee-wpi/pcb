// Compile for Arduino Leonardo
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 27
#define DATA_PIN 5

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  FastLED.showColor(CRGB(255, 255, 255), 255);
  FastLED.show();
}
