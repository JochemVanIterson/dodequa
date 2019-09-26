#ifndef SimpleSerialReceiver_h
#define SimpleSerialReceiver_h

#include "Arduino.h"

class SimpleSerialReceiver {
  public:
    SimpleSerialReceiver();
    SimpleSerialReceiver(int startByte, int stopByte, int id);
    bool match(byte *inBytes);
    long data(byte *inBytes);
    unsigned long dataUInt(byte *inBytes);
    long dataInt(byte *inBytes);
    double dataFloat(byte *inBytes);
    bool dataBool(byte *inBytes);
  private:
    byte matchData[2];
    int id;
};
#endif
