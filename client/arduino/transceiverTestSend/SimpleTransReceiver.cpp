
#include "SimpleTransReceiver.h"

SimpleTransReceiver::SimpleTransReceiver(){}
SimpleTransReceiver::SimpleTransReceiver(RF24* radio, int startByte, int stopByte, int id){
  matchData[0] = startByte;
  matchData[1] = stopByte;
  this->id = id;
  this->radio = radio;
}
bool SimpleTransReceiver::match(byte *inBytes){
  return inBytes[0] == matchData[0] && inBytes[1] == id && inBytes[4] == matchData[1];
}
long SimpleTransReceiver::data(byte *inBytes){
  return inBytes[2]*256+inBytes[3];
}
unsigned long SimpleTransReceiver::dataUInt(byte *inBytes){
  return inBytes[2]*256+inBytes[3];
}
long SimpleTransReceiver::dataInt(byte *inBytes){
  long value = inBytes[2]*256+inBytes[3];
  value -= 32768;
  return value;
}
double SimpleTransReceiver::dataFloat(byte *inBytes){
  double value = inBytes[2]*256+inBytes[3];
  value -= 32768;
  value /= 100.;
  return value;
}
bool SimpleTransReceiver::dataBool(byte *inBytes){
  return inBytes[3]!=0;
}
