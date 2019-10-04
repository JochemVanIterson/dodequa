
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"
#include "printf.h"

#include "SimpleSerialSender.h"
#include "SimpleTransSender.h"
#include "SimpleTransReceiver.h"

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);

/**********************************************************/

byte addresses[][6] = {"01Rec","01Sen"};
byte sendableArray[5] = {253, 100, 0, 0, 101};
int matchIn[2]  = {101, 251};
int matchOut[2] = {252, 100};
byte inBytesTrans[5] = {0};

//SimpleSerialSender serialSenderTest;
//SimpleTransSender senderTest;
SimpleTransReceiver transReceiverAccX;
SimpleTransReceiver transReceiverAccY;
SimpleTransReceiver transReceiverAccZ;

SimpleTransReceiver transReceiverGyroX;
SimpleTransReceiver transReceiverGyroY;
SimpleTransReceiver transReceiverGyroZ;

SimpleTransReceiver transReceiverEulerX;
SimpleTransReceiver transReceiverEulerY;
SimpleTransReceiver transReceiverEulerZ;

void setup() {
  Serial.begin(115200);
  printf_begin();
  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
//  radio.setPALevel(RF24_PA_MIN);
  radio.setPALevel(RF24_PA_MAX);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);
      
  // Start the radio listening for data
  radio.enableDynamicPayloads() ;
  radio.setAutoAck( true ) ;
  radio.powerUp() ;
  radio.startListening();

  radio.printDetails();

//  serialSenderTest = SimpleSerialSender(253, 101, 100);
//  senderTest = SimpleTransSender(&radio, 253, 101, 100);
  transReceiverAccX = SimpleTransReceiver(&radio, 252, 100, 100);
  transReceiverAccY = SimpleTransReceiver(&radio, 252, 100, 101);
  transReceiverAccZ = SimpleTransReceiver(&radio, 252, 100, 102);

  transReceiverGyroX = SimpleTransReceiver(&radio, 252, 100, 110);
  transReceiverGyroY = SimpleTransReceiver(&radio, 252, 100, 111);
  transReceiverGyroZ = SimpleTransReceiver(&radio, 252, 100, 112);
  
  transReceiverEulerX = SimpleTransReceiver(&radio, 252, 100, 120);
  transReceiverEulerY = SimpleTransReceiver(&radio, 252, 100, 121);
  transReceiverEulerZ = SimpleTransReceiver(&radio, 252, 100, 122);
}

void loop() {
/****************** Pong Back Role ***************************/  
  if(radio.available()){                                          // Variable for the received timestamp
//    while (radio.available()) {                                   // While there is data ready
      radio.read( &inBytesTrans, sizeof(inBytesTrans) );          // Get the payload
//    }
      // -------- EULER -------- //
      if(transReceiverAccX.match(inBytesTrans)){
        Serial.write(inBytesTrans, sizeof(inBytesTrans));
      } else if(transReceiverAccY.match(inBytesTrans)){
        Serial.write(inBytesTrans, sizeof(inBytesTrans));
      } else if(transReceiverAccZ.match(inBytesTrans)){
        Serial.write(inBytesTrans, sizeof(inBytesTrans));
      } else
      // -------- EULER -------- //
      if(transReceiverGyroX.match(inBytesTrans)){
        Serial.write(inBytesTrans, sizeof(inBytesTrans));
      } else if(transReceiverGyroY.match(inBytesTrans)){
        Serial.write(inBytesTrans, sizeof(inBytesTrans));
      } else if(transReceiverGyroZ.match(inBytesTrans)){
        Serial.write(inBytesTrans, sizeof(inBytesTrans));
      } else
      // -------- EULER -------- //
      if(transReceiverEulerX.match(inBytesTrans)){
        Serial.write(inBytesTrans, sizeof(inBytesTrans));
      } else if(transReceiverEulerY.match(inBytesTrans)){
        Serial.write(inBytesTrans, sizeof(inBytesTrans));
      } else if(transReceiverEulerZ.match(inBytesTrans)){
        Serial.write(inBytesTrans, sizeof(inBytesTrans));
      }
      
//    radio.stopListening();                                        // First, stop listening so we can talk
//    radio.write( &inBytesTrans, sizeof(inBytesTrans) );           // Send the final one back.
//    radio.startListening();                                       // Now, resume listening so we catch the next packets.
//    Serial.write(inBytesTrans, sizeof(inBytesTrans) );
//    Serial.print(F("Sent response "));
//    Serial.print(inBytesTrans[0]);
//    Serial.print(" ");
//    Serial.print(inBytesTrans[1]);
//    Serial.print(" ");
//    Serial.print(inBytesTrans[2]);
//    Serial.print(" ");
//    Serial.print(inBytesTrans[3]);
//    Serial.print(" ");
//    Serial.println(inBytesTrans[4]);  
  }
} // Loop

