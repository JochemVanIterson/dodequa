#include "SimpleTransSender.h"

SimpleTransSender::SimpleTransSender(){}
SimpleTransSender::SimpleTransSender(RF24* radio, int startByte, int stopByte, int id){
  dataOut[0] = startByte;
  dataOut[4] = stopByte;
  this->id = id;
  this->radio = radio;
}
void SimpleTransSender::send(int value){ // DEPRECATED
  dataOut[1] = id;
  dataOut[2] = value / 256;
  dataOut[3] = value % 256;
  if (!radio->write(&dataOut, sizeof(dataOut) )){
    Serial.println(F("Write failed"));
  }
}
void SimpleTransSender::sendUInt(unsigned long value){
  dataOut[1] = id;
  dataOut[2] = value / 256;
  dataOut[3] = value % 256;
  if (!radio->write(&dataOut, sizeof(dataOut) )){
    Serial.println(F("Write failed"));
  }
}
void SimpleTransSender::sendInt(long value){
  value += 32768;
  dataOut[1] = id;
  dataOut[2] = value / 256;
  dataOut[3] = value % 256;
  if (!radio->write(&dataOut, sizeof(dataOut) )){
    Serial.println(F("Write failed"));
  }
}
void SimpleTransSender::sendFloat(double value){
  value *= 100.;
  value += 32768;

  long outValue = (long) value;

  dataOut[1] = id;
  dataOut[2] = outValue / 256;
  dataOut[3] = outValue % 256;
  if (!radio->write(&dataOut, sizeof(dataOut) )){
    Serial.println(F("Write failed"));
  }
}
void SimpleTransSender::sendBool(bool value){
  dataOut[1] = id;
  dataOut[3] = value;
  if (!radio->write(&dataOut, sizeof(dataOut) )){
    Serial.println(F("Write failed"));
  }
}
