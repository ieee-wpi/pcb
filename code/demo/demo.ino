/*
* Essentials of PCB Design
* Demo: Utilizes the onboard button to cycle through three animations.
* 
* Track 1 boards compile for Arduino Leonardo
* Requirements:
* - FastLED library
* - Bounce2 library
*/

#include <FastLED.h>
#include <Bounce2.h>

// Board-specific pins
#define NUM_LEDS 27
#define DATA_PIN 5
#define BUTTON_PIN 7

// Brightness of all LEDs (0-255)
#define BRIGHTNESS 50

// Number of effects
#define NUM_EFFECTS 3

// Display modes
enum Effect {
	rainbow,
	letters,
	noise
};

// Set current effect
volatile Effect currentEffect = rainbow;

// Array of LEDs
CRGB leds[NUM_LEDS];

// Button debouncer
Bounce debouncer = Bounce();

// Rainbow effect parameters
volatile uint8_t rainbowHue = 0;
volatile uint8_t rainbowLed = 0;

// Letter effect parameters
constexpr int letterPos[] = {0, 13, 22};
volatile uint8_t letterIndex = 0;
volatile uint8_t letterBright = 0;
constexpr uint16_t letterSwitchTime = 2000;
static CEveryNMillis letterTimer(letterSwitchTime);

// Noise effect parameters
volatile uint32_t noiseColor = 0;
volatile uint32_t noiseAlpha = 2000;
const CRGBPalette16 noisePalette = OceanColors_p;


// Setup function - runs once at the start
void setup() {
	FastLED.addLeds<WS2812,DATA_PIN,GRB>(leds,NUM_LEDS);
	FastLED.setBrightness(BRIGHTNESS);

	debouncer.attach(BUTTON_PIN, INPUT_PULLUP);
	debouncer.interval(25);
}

// Loop function - repeatedly called after setup()
void loop() {
	switch (currentEffect) {
		case rainbow: {
			displayRainbow();
			break;
		}
		case letters: {
			displayLetters();
			break;
		}
		case noise: {
			displayNoise();
			break;
		}
	}

	debouncer.update();

	if (debouncer.fell()) {
		buttonCallback();
	}
}

// Rainbow effect
void displayRainbow() {
	// Cycle rainbow effect
	EVERY_N_MILLISECONDS(60) {
		// Fade all LEDs
		fadeAll(200);

		// Light up the current LED
		leds[rainbowLed] = CHSV(rainbowHue, 255, 255);
		FastLED.show();

		// Increment led and hue
		rainbowLed++;
		rainbowHue += 3;

		// Reset LED at end
		if (rainbowLed >= NUM_LEDS) {
			rainbowLed = 0;
		}
	}
}

// Letters effect
void displayLetters() {
	// Fade in current letter
	EVERY_N_MILLISECONDS(15) {
		// Fade all LEDs
		fadeAll(240);

		if (letterBright < 255) letterBright += 5;

		// Calculate start and end LEDs
		uint8_t start = letterPos[letterIndex];
		uint8_t end = letterIndex == 2 ? NUM_LEDS : letterPos[letterIndex + 1];

		for(int i = start; i < end; i++) {
			leds[i] = CHSV(0, 255, letterBright);
		}
		
		FastLED.show();
  }

	// Increment current letter
	if (letterTimer) {
		letterIndex = (letterIndex + 1) % 3;
		letterBright = 0;
	}
}

// Noise effect
void displayNoise() {
	// Display noise
  EVERY_N_MILLISECONDS(60) {
    noiseColor += 2;
		noiseAlpha += 10;

		for (int i = 0; i < NUM_LEDS; i++) {
			// Generate an 8-bit color index from noise
			uint8_t colorIndex = inoise8(i * 40, noiseColor);

			// Generate an alpha value mapped to the brightness macro
			uint8_t alpha = inoise8(i * 70, noiseAlpha);
			alpha = constrain(map(alpha, 100, 200, 0, 255), 0, 255);

			// Map noise value to a palette color
			leds[i] = ColorFromPalette(noisePalette, colorIndex, alpha, LINEARBLEND);
		}
	}

  FastLED.show();
}

// Scales the brightness of all LEDs
void fadeAll(uint8_t strength) {
  for (int i = 0; i < NUM_LEDS; i++) { 
    leds[i].nscale8(strength);
  }
}

// Callback function for button press
void buttonCallback() {
	// Increment current effect
	currentEffect = (currentEffect + 1) % NUM_EFFECTS;
	
	// Reset effect parameters
	rainbowHue = 0;
	rainbowLed = 0;
	
	letterIndex = 0;
	letterBright = 0;
	letterTimer.reset();

	noiseColor = 0;
	noiseAlpha = 2000;

	// Clear LEDs
	FastLED.clear();
}
