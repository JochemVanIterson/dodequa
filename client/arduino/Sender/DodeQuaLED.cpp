#include "DodeQuaLED.h"

DodeQuaLED::DodeQuaLED(){}
DodeQuaLED::DodeQuaLED(int brightness){
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(this->leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  this->brightness = brightness;
}

void DodeQuaLED::setLED(int index, int r, int g, int b) {
  this->leds[index] = CRGB(r, g, b);
}

void DodeQuaLED::setLEDS(int r, int g, int b) {
  this->red = r;
  this->green = g;
  this->blue = b;
  this->setLED(0, r, g, b);
  this->setLED(1, b, r, g);
}

void DodeQuaLED::showLEDS(int delTime) {
  if(millis() >= this->lastUpdate + delTime) {
    FastLED.setBrightness(this->brightness);
    FastLED.show();
    this->lastUpdate = millis();
  }
}

void DodeQuaLED::randomLEDS() {
  if(millis() >= lastChanged+this->randomSpeed) {
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
  this->rainbowSpeed = speed;
}
void DodeQuaLED::initRandomLEDS(int speed) {
  this->randomSpeed = speed;
}
void DodeQuaLED::initPulseLEDS(int speed) {
  this->pulseSpeed = speed;
  this->pulseDirection = random(0,2);
}

void DodeQuaLED::rainbowLEDS() {
  if(this->red > 0 && this->green <= 255 && this->blue == 0) {
    if(millis() >= this->lastChanged+this->rainbowSpeed) {
      if(this->red>0)this->red--;
      if(this->green<255)this->green++;
      this->setLEDS(this->red, this->green, this->blue);
      this->lastChanged = millis();
    }
  } else
  if(this->red == 0 && this->green > 0 && this->blue <= 255) {
    if(millis() >= this->lastChanged+this->rainbowSpeed) {
      if(this->green>0)this->green--;
      if(this->blue<255)this->blue++;
      this->setLEDS(this->red, this->green, this->blue);
      this->lastChanged = millis();
    }
  } else
  if(this->red <= 255 && this->green == 0 && this->blue > 0) {
    if(millis() >= this->lastChanged+this->rainbowSpeed) {
      if(this->blue>0)this->blue--;
      if(this->red<255)this->red++;
      this->setLEDS(this->red, this->green, this->blue);
      this->lastChanged = millis();
    }
  } else {
    if(millis() >= this->lastChanged+this->rainbowSpeed) {
      if(this->red<255)this->red++;
      if(this->blue>0)this->blue--;
      if(this->green>0)this->blue--;
      this->setLEDS(this->red, this->green, this->blue);
      this->lastChanged = millis();
    }
  }
}

void DodeQuaLED::pulseLEDS() {
  if(millis() >= this->lastChanged+this->pulseSpeed) {
    if((this->red==this->blue) && (this->red==this->green)){
      if(pulseDirection){
        this->red--;
        this->blue--;
        this->green--;
        if(this->red<=10)pulseDirection=false;
      } else {
        this->red++;
        this->blue++;
        this->green++;
        if(this->red>=255)pulseDirection=true;
      }
    } else {
      if(pulseDirection){
        if(this->red>10)this->red--;
        if(this->blue>10)this->blue--;
        if(this->green>10)this->green--;
      } else {
        if(this->red<254)this->red++;
        if(this->blue<254)this->blue++;
        if(this->green<254)this->green++;
      }
    }
    this->setLEDS(this->red, this->green, this->blue);
    this->lastChanged = millis();
  }
}
