#ifndef SimpleTransSender_h
#define SimpleTransSender_h

#include "Arduino.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

class SimpleTransSender {
  public:
    SimpleTransSender();
    SimpleTransSender(RF24 *radio, int startByte, int stopByte, int id);
    void send(int value);
    void sendUInt(unsigned long value);
    void sendInt(long value);
    void sendFloat(double value);
    void sendBool(bool value);
  private:
    RF24 *radio;
    byte dataOut[5];
    int id;
};
#endif
