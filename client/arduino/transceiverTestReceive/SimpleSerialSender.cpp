#include "SimpleSerialSender.h"

SimpleSerialSender::SimpleSerialSender(){}
SimpleSerialSender::SimpleSerialSender(int startByte, int stopByte, int id){
  dataOut[0] = startByte;
  dataOut[4] = stopByte;
  this->id = id;
}
void SimpleSerialSender::send(int value){ // DEPRECATED
  dataOut[1] = id;
  dataOut[2] = value / 256;
  dataOut[3] = value % 256;
  Serial.write(dataOut,5);
}
void SimpleSerialSender::sendUInt(unsigned long value){
  dataOut[1] = id;
  dataOut[2] = value / 256;
  dataOut[3] = value % 256;
  Serial.write(dataOut,5);
}
void SimpleSerialSender::sendInt(long value){
  value += 32768;
  dataOut[1] = id;
  dataOut[2] = value / 256;
  dataOut[3] = value % 256;
  Serial.write(dataOut,5);
}
void SimpleSerialSender::sendFloat(double value){
  value *= 100.;
  value += 32768;

  long outValue = (long) value;

  dataOut[1] = id;
  dataOut[2] = outValue / 256;
  dataOut[3] = outValue % 256;
  Serial.write(dataOut,5);
}
void SimpleSerialSender::sendBool(bool value){
  dataOut[1] = id;
  dataOut[3] = value;
  Serial.write(dataOut,5);
}
