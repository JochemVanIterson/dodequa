#include "DodeQuaLED.h"

DodeQuaLED::DodeQuaLED(){}
DodeQuaLED::DodeQuaLED(int brightness){
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(this->leds, NUM_LEDS);
  LEDS.setBrightness(brightness);
}

void DodeQuaLED::setLED(int index, int r, int g, int b) {
  this->leds[index] = CRGB(r, g, b);
}

void DodeQuaLED::setLEDS(int r, int g, int b) {
  this->setLED(0, r, g, b);
  this->setLED(1, b, r, g);
}

void DodeQuaLED::showLEDS(int delTime) {
  if(millis() >= this->lastUpdate + delTime) {
    Serial.println(this->lastUpdate + delTime);
    FastLED.show();
    this->lastUpdate = millis();
  }
}

void DodeQuaLED::randomLEDS() {
  if(millis() >= lastChanged+500) {
    Serial.println("Loop");
    this->red   = random(0, 255);
    this->green = random(0, 255);
    this->blue  = random(0, 255);
    this->setLEDS(this->red, this->green, this->blue);
    FastLED.show();
    this->lastChanged = millis();
  }
}

void DodeQuaLED::initRainbowLEDS(int speed) {
  this->red = 255;
  this->green = 0;
  this->blue = 0;
  this->rainbowSpeed = speed;
}

void DodeQuaLED::rainbowLEDS() {
  if(this->red > 0 && this->green < 255 && this->blue == 0) {
    if(millis() >= this->lastChanged+this->rainbowSpeed) {
      this->red--;
      this->green++;
      this->setLEDS(this->red, this->green, this->blue);
      this->lastChanged = millis();
    }
  } else
  if(this->red == 0 && this->green > 0 && this->blue < 255) {
    if(millis() >= this->lastChanged+this->rainbowSpeed) {
      this->green--;
      this->blue++;
      this->setLEDS(this->red, this->green, this->blue);
      this->lastChanged = millis();
    }
  } else
  if(this->red < 255 && this->green == 0 && this->blue > 0) {
    if(millis() >= this->lastChanged+this->rainbowSpeed) {
      this->blue--;
      this->red++;
      this->setLEDS(this->red, this->green, this->blue);
      this->lastChanged = millis();
    }
  }
}
