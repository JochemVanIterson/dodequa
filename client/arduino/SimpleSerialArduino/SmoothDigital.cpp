#include "SmoothDigital.h"

SmoothDigital::SmoothDigital(){}
SmoothDigital::SmoothDigital(int inputPin, unsigned long debounceDelay){
  this->inputPin = inputPin;
  this->debounceDelay = debounceDelay;
}
int SmoothDigital::read(){
  int reading = digitalRead(inputPin);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      lastButtonState = reading;
      return buttonState;
    }
  }
  
  lastButtonState = reading;
  return -1;
}

