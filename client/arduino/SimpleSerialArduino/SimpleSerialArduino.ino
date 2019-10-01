#include "SimpleSerialSender.h"
#include "SimpleSerialReceiver.h"
// #include "SimpleTransSender.h"
// #include "SimpleTransReceiver.h"
#include "SmoothDigital.h"
#include "SmoothAnalog.h"

// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>

// -------------- PINS -------------- //
int ledPin = 13;

// -------------- VARS -------------- //
byte inBytes[5];
int matchIn[2]  = {101, 251};
int matchOut[2] = {252, 100};
unsigned long lastMillis = 0;

// ------------ SERIALS ------------- //
SimpleSerialSender debugSerialS;
SimpleSerialReceiver ledSerialR;

// -------------- TRANSCEIVERS -------------- //
// RF24 radio(7, 8); // CE, CSN
// byte inBytesTrans[5];
// const byte addressReceive[6] = "00001";
// const byte addressSend[6]    = "00002";

// SimpleTransSender debugTransS;
// SimpleTransReceiver ledTransR;

void setup() {
  Serial.begin(115200);

  // -------------- Serial -------------- //
  debugSerialS = SimpleSerialSender(matchOut[0], matchOut[1], 100);
  ledSerialR = SimpleSerialReceiver(matchIn[0], matchIn[1], 101);

  // -------------- Transceiver -------------- //
  // radio.begin();
  // radio.openWritingPipe(addressSend); // 00002
  // radio.openReadingPipe(1, addressReceive); // 00001
  // radio.setPALevel(RF24_PA_MIN);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  getSerial(inBytes);
  // getTransceiver(inBytesTrans);
  if((millis()-lastMillis)>10){
    lastMillis = millis();
    debugSerialS.sendFloat(lastMillis/1000.);
  }
  // ------------ SERIAL IN ------------- //
  if(ledSerialR.match(inBytes)){ // LED 1
    if(ledSerialR.dataBool(inBytes)==0)digitalWrite(ledPin, LOW);
    else digitalWrite(ledPin, HIGH);
  }

  // if(ledTransR.match(inBytes)){ // LED 1
  //   if(ledTransR.dataBool(inBytes))digitalWrite(ledPin, LOW);
  //   else digitalWrite(ledPin, HIGH);
  // }

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
// void getTransceiver(byte* inBytesTrans){
//   radio.startListening();
//   if (radio.available()) {
//     radio.read((char*)inBytes,4);
//   }
//   radio.stopListening();
// }
void clearInput() {
  // clearInput: functie om de array met inkomende data leeg te maken,
  // om te voorkomen dat de match nog een keer gelijk is.
  memset(inBytes,0,sizeof(inBytes));
  // memset(inBytesTrans,0,sizeof(inBytesTrans));
}
