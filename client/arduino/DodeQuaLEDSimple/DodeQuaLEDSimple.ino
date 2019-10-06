#define FASTLED_FORCE_SOFTWARE_SPI
#include "FastLED.h"
// Led animations

// How many leds in your strip?
#define NUM_LEDS 2

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 2

// Define the array of leds
CRGB leds[NUM_LEDS];

unsigned long lastMillis;

int red;    //
int green;  // 0 - 255, might need mapping
int blue;   //

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  LEDS.setBrightness(10);
}

void loop() {
  if(millis() >= lastMillis+500) {
    Serial.println("Loop");
    red = random(0, 255);
    green = random(0, 255);
    blue = random(0, 255);

    leds[0] = CRGB(red, green, blue);
    leds[1] = CRGB(red, green, blue);
    FastLED.show();
    lastMillis = millis();
  }
}
