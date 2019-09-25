#include "SmoothAnalog.h"

SmoothAnalog::SmoothAnalog(){}
SmoothAnalog::SmoothAnalog(int inputPin, int smoothing){
  this->inputPin = inputPin;
  this->smoothing = smoothing;
  for (int thisReading = 0; thisReading < smoothing; thisReading++) {
    dataArray[thisReading] = 0;
  }
}
int SmoothAnalog::read(){
  total = total - dataArray[readIndex];
  dataArray[readIndex] = analogRead(inputPin);
  total = total + dataArray[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= smoothing) {
    readIndex = 0;
  }
  average = total / smoothing;
  return average;
}

