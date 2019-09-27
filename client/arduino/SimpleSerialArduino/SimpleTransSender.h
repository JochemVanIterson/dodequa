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
    void sendUInt(int value);
    void sendInt(int value);
    void sendFloat(int value);
    void sendBool(int value);
  private:
    byte dataOut[5];
    int id;
};
#endif
