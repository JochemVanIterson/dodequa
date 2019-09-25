#include "SimpleSerialSender.h"
#include "SimpleSerialReceiver.h"
#include "SmoothDigital.h"
#include "SmoothAnalog.h"

// -------------- PINS -------------- //

// -------------- VARS -------------- //
byte inBytes[5];
void setup() {
  Serial.begin(115200);

  debugSerialS = SimpleSerialSender(matchOut[0], matchOut[1], 100);
}

void loop() {
  getSerial(inBytes);
 if((millis()-lastMillis)>1000){
   lastMillis = millis();
   debugSerialS.send(lastMillis);
 }

  clearInput();
}

void getSerial(byte* inBytes){
  // getSerial: functie om de seriële data binnen te halen en
  // op te slaan in de variabele inBytes
  if (Serial.available()) {
    Serial.readBytes((char*)inBytes,4);
    return;
  }
}
void clearInput() {
  // clearInput: functie om de array met inkomende data leeg te maken,
  // om te voorkomen dat de match nog een keer gelijk is.
  memset(inBytes,0,sizeof(inBytes));
}
