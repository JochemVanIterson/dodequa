#include "SimpleSerialReceiver.h"

SimpleSerialReceiver::SimpleSerialReceiver(){}
SimpleSerialReceiver::SimpleSerialReceiver(int startByte, int stopByte, int id){
  matchData[0] = startByte;
  matchData[1] = stopByte;
  this->id = id;
}
