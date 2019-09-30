#ifndef SimpleTransReceiver_h
#define SimpleTransReceiver_h

#include "Arduino.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "SimpleSerialSender.h"

class SimpleTransReceiver {
  public:
    SimpleTransReceiver();
    SimpleTransReceiver(RF24 *radio, int startByte, int stopByte, int id);
    bool match(byte *inBytes);
    long data(byte *inBytes);
    unsigned long dataUInt(byte *inBytes);
    long dataInt(byte *inBytes);
    double dataFloat(byte *inBytes);
    bool dataBool(byte *inBytes);
    void pass(SimpleSerialSender* sender, byte *inBytes);
  private:
    byte matchData[2];
    RF24 *radio;
    int id;
};
#endif
