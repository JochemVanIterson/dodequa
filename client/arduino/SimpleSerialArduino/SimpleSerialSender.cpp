#include "SimpleSerialSender.h"

SimpleSerialSender::SimpleSerialSender(){}
SimpleSerialSender::SimpleSerialSender(int startByte, int stopByte, int id){
  dataOut[0] = startByte;
  dataOut[4] = stopByte;
  this->id = id;
}
