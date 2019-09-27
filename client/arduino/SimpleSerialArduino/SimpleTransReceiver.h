#ifndef SimpleTransReceiver_h
#define SimpleTransReceiver_h

#include "Arduino.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

class SimpleTransReceiver {
  public:
    SimpleTransReceiver();
    SimpleTransReceiver(RF24 *radio, int id);
    bool match();
    double data();
    unsigned long dataUInt(byte *inBytes);
    long dataInt(byte *inBytes);
    double dataFloat(byte *inBytes);
    bool dataBool(byte *inBytes);
  private:
    int id;
};
#endif
