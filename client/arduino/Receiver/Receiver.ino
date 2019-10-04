/*
* Arduino Wireless Communication Tutorial
*     Example 2 - Receiver Code
*
* by Dejan Nedelkovski, www.HowToMechatronics.com
*
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// RF24 radio(7, 8); // CE, CSN    // Arduino
RF24 radio(1, 0); // CE, CSN      // Teensy

const byte addresses[][6] = {"00001", "00002"};
void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
}
void loop() {
  radio.startListening();
  if ( radio.available()) {
    byte inBytesTrans[5];
    radio.read(inBytesTrans, 5);
    Serial.print(inBytesTrans[0]);
    Serial.print(inBytesTrans[1]);
    Serial.print(inBytesTrans[2]);
    Serial.print(inBytesTrans[3]);
    Serial.println(inBytesTrans[4]);
    // myServo.write(angleV);
  }
  radio.stopListening();
  // buttonState = digitalRead(button);
  // radio.write(&buttonState, sizeof(buttonState));
}
