#include "SimpleTransSender.h"

SimpleTransSender::SimpleTransSender(){}
SimpleTransSender::SimpleTransSender(RF24* radio, int startByte, int stopByte, int id){
  dataOut[0] = startByte;
  dataOut[4] = stopByte;
  this->id = id;
  this->radio = radio;
}
void SimpleTransSender::send(int value){ // DEPRECATED
//  dataOut[1] = id;
//  dataOut[2] = value / 256;
//  dataOut[3] = value % 256;
//  if (!radio->write(&dataOut, sizeof(dataOut) )){
//    Serial.println(F("Write failed"));
//  } else Serial.println(F("Write success"));
  this->sendData(value/256, value%256);
}
void SimpleTransSender::sendUInt(unsigned long value){
//  dataOut[1] = id;
//  dataOut[2] = value / 256;
//  dataOut[3] = value % 256;
//  if (!radio->write(&dataOut, sizeof(dataOut) )){
//    Serial.println(F("Write failed"));
//  } else Serial.println(F("Write success"));
  this->sendData(value/256, value%256);
}
void SimpleTransSender::sendInt(long value){
  value += 32768;
//  dataOut[1] = id;
//  dataOut[2] = value / 256;
//  dataOut[3] = value % 256;
//  if (!radio->write(&dataOut, sizeof(dataOut) )){
//    Serial.println(F("Write failed"));
//  } else Serial.println(F("Write success"));

  this->sendData(value/256, value%256);
}
void SimpleTransSender::sendFloat(double value){
  value *= 100.;
  value += 32768;

  long outValue = (long) value;

  this->sendData(outValue/256, outValue%256);
}
void SimpleTransSender::sendBool(bool value){
  this->sendData(0, value);
}

void SimpleTransSender::sendData(byte b1, byte b2){
  dataOut[1] = id;
  dataOut[2] = b1;
  dataOut[3] = b2;
  if (!radio->write(&dataOut, sizeof(dataOut) )){
    Serial.println(F("Write failed"));
  } else Serial.println(F("Write success"));
//  delay(10);
}
