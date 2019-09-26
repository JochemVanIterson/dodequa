#include "SimpleSerialReceiver.h"

SimpleSerialReceiver::SimpleSerialReceiver(){}
SimpleSerialReceiver::SimpleSerialReceiver(int startByte, int stopByte, int id){
  matchData[0] = startByte;
  matchData[1] = stopByte;
  this->id = id;
}
bool SimpleSerialReceiver::match(byte *inBytes){
  return inBytes[0] == matchData[0] && inBytes[1] == id && inBytes[4] == matchData[1];
}
long SimpleSerialReceiver::data(byte *inBytes){
  return inBytes[2]*256+inBytes[3];
}
unsigned long SimpleSerialReceiver::dataUInt(byte *inBytes){
  return inBytes[2]*256+inBytes[3];
}
long SimpleSerialReceiver::dataInt(byte *inBytes){
  long value += inBytes[2]*256+inBytes[3];
  value -= 32.768;
  return value;
}
unsigned double SimpleSerialReceiver::dataUFloat(byte *inBytes){
  long value += inBytes[2]*256+inBytes[3];
  value /= 100.;
  return value;
}
double SimpleSerialReceiver::dataFloat(byte *inBytes){
  long value += inBytes[2]*256+inBytes[3];
  value -= 32.768;
  value /= 100.;
  return value;
}
bool SimpleSerialReceiver::dataBool(byte *inBytes){
  return inBytes[3]!=0;
}
