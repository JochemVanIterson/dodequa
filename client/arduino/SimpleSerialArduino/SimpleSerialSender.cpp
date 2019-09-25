#include "SimpleSerialSender.h"

SimpleSerialSender::SimpleSerialSender(){}
SimpleSerialSender::SimpleSerialSender(int startByte, int stopByte, int id){
  dataOut[0] = startByte;
  dataOut[4] = stopByte;
  this->id = id;
}
void SimpleSerialSender::send(String type, int value){
  dataOut[1] = id;
  dataOut[2] = value / 256;
  dataOut[3] = value % 256;
  Serial.write(dataOut,5);
}
