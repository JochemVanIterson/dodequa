#ifndef SimpleSerialSender_h
#define SimpleSerialSender_h

#include "Arduino.h"

class SimpleSerialSender {
  public:
    SimpleSerialSender();
    SimpleSerialSender(int startByte, int stopByte, int id);
    void send(int value); // DEPRECATED
    void sendUInt(int value);
    void sendInt(int value);
    void sendUFloat(int value);
    void sendFloat(int value);
    void sendBool(int value);
  private:
    byte dataOut[5];
    int id;
};
#endif
