#include "DodeQuaLED.h"

DodeQuaLED rgbLed(255);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  rgbLed.initRainbowLEDS(20);
}

void loop() {
  rgbLed.rainbowLEDS();
  rgbLed.showLEDS(10);
}
