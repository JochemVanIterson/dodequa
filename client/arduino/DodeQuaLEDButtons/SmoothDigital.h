#ifndef SmoothDigital_h
#define SmoothDigital_h

#include "Arduino.h"

class SmoothDigital {
  public:
    SmoothDigital();
    SmoothDigital(int inputPin, unsigned long debounceDelay);
    int read();
  private:
    int inputPin;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay;
    
    int buttonState;
    int lastButtonState = LOW;
    
};
#endif

