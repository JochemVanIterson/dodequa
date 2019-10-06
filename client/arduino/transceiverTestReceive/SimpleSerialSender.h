#ifndef SimpleSerialSender_h
#define SimpleSerialSender_h

#include "Arduino.h"

class SimpleSerialSender {
  public:
    SimpleSerialSender();
    SimpleSerialSender(int startByte, int stopByte, int id);
    void send(int value); // DEPRECATED
    void sendUInt(unsigned long value);
    void sendInt(long value);
    void sendFloat(double value);
    void sendBool(bool value);
  private:
    byte dataOut[5];
    int id;
};
#endif
