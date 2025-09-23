/*
* Essentials of PCB Design
* Rainbow: Iterates back and forth across the LEDs, changing their hue.
* 
* Track 1 boards compile for Arduino Leonardo
* Requirements:
* - FastLED library
*/

#include <FastLED.h>

// You may need to change these for your board
#define NUM_LEDS 30
#define DATA_PIN 5

// Delay after each loop iteration (ms)
#define DELAY 50
// Brightness of all LEDs (0-255)
#define BRIGHTNESS 50

// Array of LEDs
CRGB leds[NUM_LEDS];

// Scales the brightness of all the LEDs
void fadeall() {
  for(int i = 0; i < NUM_LEDS; i++) { 
    leds[i].nscale8(250);
  }
}

// Setup function - runs once at the start
void setup() { 
	FastLED.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	FastLED.setBrightness(BRIGHTNESS);
}

// Loop function - repeatedly called after setup()
void loop() { 
	static uint8_t hue = 0;

	// Slide the leds in one direction
	for(int i = 0; i < NUM_LEDS; i++) {
    // Advance hue of current LED and write to LEDs
		leds[i] = CHSV(hue++, 255, 255);
		FastLED.show(); 

    // Fade all LEDs and wait
		fadeall();
		delay(DELAY);
	}

	// Slide the leds in the other direction.
	for(int i = NUM_LEDS-1; i >= 0; i--) {
    // Advance hue of current LED and write to LEDs
		leds[i] = CHSV(hue++, 255, 255);
		FastLED.show();

    // Fade all LEDs and wait
		fadeall();
		delay(DELAY);
	}
}
