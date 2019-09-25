#ifndef SimpleSerialReceiver_h
#define SimpleSerialReceiver_h

#include "Arduino.h"

class SimpleSerialReceiver {
  public:
    SimpleSerialReceiver();
    SimpleSerialReceiver(int startByte, int stopByte, int id);
  private:
};
#endif

