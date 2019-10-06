#ifndef SmoothAnalog_h
#define SmoothAnalog_h

#include "Arduino.h"

class SmoothAnalog {
  public:
    SmoothAnalog();
    SmoothAnalog(int smoothing);
    double read(double input);
  private:
    double dataArray[2048];
    int smoothing;

    int readIndex = 0;              // the index of the current reading
    int total = 0;                  // the running total
    int average = 0;                // the average

};
#endif
