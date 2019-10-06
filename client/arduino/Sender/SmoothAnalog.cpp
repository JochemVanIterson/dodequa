#include "SmoothAnalog.h"

SmoothAnalog::SmoothAnalog(){}
SmoothAnalog::SmoothAnalog(int smoothing){
  this->smoothing = smoothing;
  for (int thisReading = 0; thisReading < smoothing; thisReading++) {
    dataArray[thisReading] = 0;
  }
}
double SmoothAnalog::read(double input){
  total = total - dataArray[readIndex];
  dataArray[readIndex] = input;
  total = total + dataArray[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= smoothing) {
    readIndex = 0;
  }
  average = total / smoothing;
  return average;
}
