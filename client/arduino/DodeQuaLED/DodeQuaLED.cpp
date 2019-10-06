#include "DodeQuaLED.h"

DodeQuaLED::DodequaLED() {
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  LEDS.setBrightness(83);
}

void DodeQuaLED::setLEDS(gyroX, gyroY, gyroZ) {
  this->redInput = gyroX;
  this->greenInput = gyroY;
  this ->blueInput = gyroZ;

  RED = map(redInput, 0, 360, 0, 255);
  GREEN = map(greenInput, 0, 360, 0 255);
  BLUE = map(blueInput, 0, 360, 0, 255);

  leds[0] = CRGB(RED, GREEN, BLUE);
  leds[1] = CRGB(GREEN, BLUE, RED);
  FastLED.show();
  delay(10);
}

void DodeQuaLED::randomLEDS() {
  RED = random(0, 250);
  GREEN = random(0,250);
  BLUE = random(0,250);

  leds[0] = CRGB(RED, GREEN, BLUE);
  leds[1] = CRGB(GREEN, BLUE, RED);
  FastLED.show();
  delay(500);
}

void DodeQuaLED::rainbowLEDS() {
  RED = 250;
  GREEN = 0;
  BLUE = 0;
  while(RED > 0) {
    RED--;
    GREEN++;
    leds[0] = CRGB(RED, GREEN, BLUE);
    leds[1] = CRGB(GREEN, BLUE, RED);
    FastLED.show();
    fadeallfast();
    delay(5);
  }
  while(GREEN > 0) {
    GREEN--;
    BLUE++;
    leds[0] = CRGB(RED, GREEN, BLUE);
    leds[1] = CRGB(GREEN, BLUE, RED);
    FastLED.show();
    fadeallfast();
    delay(5);
  }
  while(BLUE > 0) {
    BLUE--;
    RED++;
    leds[0] = CRGB(RED, GREEN, BLUE);
    leds[1] = CRGB(GREEN, BLUE, RED);
    FastLED.show();
    fadeallfast();
    delay(5);
  }
}
