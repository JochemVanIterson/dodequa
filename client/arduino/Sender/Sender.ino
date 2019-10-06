#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include <SPI.h>
#include "RF24.h"
#include "printf.h"

#include "SimpleSerialSender.h"
#include "SimpleSerialReceiver.h"
#include "SimpleTransSender.h"
#include "SimpleTransReceiver.h"

// ---------------------------------- PINS ---------------------------------- //
//int ledPin = 13;

// ---------------------------------- 9DOF ---------------------------------- //
Adafruit_BNO055 bno = Adafruit_BNO055();

// ---------------------------- Transceiver vars ---------------------------- //
RF24 radio(7,8);
byte addresses[][6] = {"01Rec","01Sen"};
byte sendableArray[5] = {253, 100, 0, 0, 101};
byte inBytesTrans[5] = {0};

// ------------------------------ TRANSCEIVERS ------------------------------ //
SimpleTransReceiver receiverTest;

SimpleTransSender transSendAccX;
SimpleTransSender transSendAccY;
SimpleTransSender transSendAccZ;
SimpleTransSender transSendGyroX;
SimpleTransSender transSendGyroY;
SimpleTransSender transSendGyroZ;
SimpleTransSender transSendEulerX;
SimpleTransSender transSendEulerY;
SimpleTransSender transSendEulerZ;

// ------------------------------- Serial vars ------------------------------ //
byte inBytes[5];
int matchIn[2]  = {101, 251};
int matchOut[2] = {252, 100};
unsigned long lastMillis = 0;

// -------------------------------- SERIALS --------------------------------- //
//SimpleSerialSender serialSendAccX;
//SimpleSerialSender serialSendAccY;
//SimpleSerialSender serialSendAccZ;
//SimpleSerialSender serialSendGyroX;
//SimpleSerialSender serialSendGyroY;
//SimpleSerialSender serialSendGyroZ;
//SimpleSerialSender serialSendEulerX;
//SimpleSerialSender serialSendEulerY;
//SimpleSerialSender serialSendEulerZ;

void setup(void){
  // -------------- Open serial -------------- //
  Serial.begin(115200);
//  while (!Serial); // Wait for serial connection

  printf_begin();
  Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");

  // -------------- Open transceiver -------------- //
  openTransceiver();

  // -------------- Set Pins -------------- //
//  pinMode(ledPin, OUTPUT);

  // -------------- Init 9DOF Sensor -------------- //
  if(!bno.begin()){
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  bno.setExtCrystalUse(true);

  // -------------- Init Serial ports -------------- //
//  serialSendAccX = SimpleSerialSender(matchOut[0], matchOut[1], 100);
//  serialSendAccY = SimpleSerialSender(matchOut[0], matchOut[1], 101);
//  serialSendAccZ = SimpleSerialSender(matchOut[0], matchOut[1], 102);
//  serialSendGyroX = SimpleSerialSender(matchOut[0], matchOut[1], 110);
//  serialSendGyroY = SimpleSerialSender(matchOut[0], matchOut[1], 111);
//  serialSendGyroZ = SimpleSerialSender(matchOut[0], matchOut[1], 112);
//  serialSendEulerX = SimpleSerialSender(matchOut[0], matchOut[1], 120);
//  serialSendEulerY = SimpleSerialSender(matchOut[0], matchOut[1], 121);
//  serialSendEulerZ = SimpleSerialSender(matchOut[0], matchOut[1], 122);

  // -------------- Init Transceiver ports -------------- //
  receiverTest = SimpleTransReceiver(&radio, matchOut[0], matchOut[1], 100);

  transSendAccX = SimpleTransSender(&radio, matchOut[0], matchOut[1], 100);
  transSendAccY = SimpleTransSender(&radio, matchOut[0], matchOut[1], 101);
  transSendAccZ = SimpleTransSender(&radio, matchOut[0], matchOut[1], 102);
  transSendGyroX = SimpleTransSender(&radio, matchOut[0], matchOut[1], 110);
  transSendGyroY = SimpleTransSender(&radio, matchOut[0], matchOut[1], 111);
  transSendGyroZ = SimpleTransSender(&radio, matchOut[0], matchOut[1], 112);
  transSendEulerX = SimpleTransSender(&radio, matchOut[0], matchOut[1], 120);
  transSendEulerY = SimpleTransSender(&radio, matchOut[0], matchOut[1], 121);
  transSendEulerZ = SimpleTransSender(&radio, matchOut[0], matchOut[1], 122);
}

void loop(void){
  radio.stopListening();
//  digitalWrite(ledPin, HIGH);

  imu::Vector<3> acc   = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  imu::Vector<3> gyro  = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

//  serialSendAccX.sendFloat(acc.x());
//  serialSendAccY.sendFloat(acc.y());
//  serialSendAccZ.sendFloat(acc.z());
//  serialSendGyroX.sendFloat(gyro.x());
//  serialSendGyroY.sendFloat(gyro.y());
//  serialSendGyroZ.sendFloat(gyro.z());
//  serialSendEulerX.sendFloat(euler.x());
//  serialSendEulerY.sendFloat(euler.y());
//  serialSendEulerZ.sendFloat(euler.z());

//   transSendAccX.sendFloat(millis()/100.);
  transSendAccX.sendFloat(acc.x());
  transSendAccY.sendFloat(acc.y());
  transSendAccZ.sendFloat(acc.z());
  transSendGyroX.sendFloat(gyro.x());
  transSendGyroY.sendFloat(gyro.y());
  transSendGyroZ.sendFloat(gyro.z());
  transSendEulerX.sendFloat(euler.x());
  transSendEulerY.sendFloat(euler.y());
  transSendEulerZ.sendFloat(euler.z());

//  radio.startListening();
//
//  unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
//  boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
//
//  while(!radio.available()){                                 // While nothing is received
//    if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
//      timeout = true;
//      break;
//    }
//  }
//
//  if ( timeout ){                                            // Describe the results
//    Serial.println(F("Failed, response timed out."));
//  } else {
//    double got_time;                                  // Grab the response, compare, and send to debugging spew
//    radio.read( &inBytesTrans, sizeof(inBytesTrans) );
//    got_time = receiverTest.dataFloat(inBytesTrans);
//    unsigned long end_time = micros();
//
//    // Spew it
//    Serial.println(F("Sent"));
//  }

//  delay(100);
}

void openTransceiver(){
  SPI.setSCK(13);
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
//  radio.setPALevel(RF24_PA_MIN);
  radio.setPALevel(RF24_PA_MAX);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);

  // Start the radio listening for data
  radio.enableDynamicPayloads() ;
  radio.setAutoAck( true ) ;
  radio.powerUp() ;
  radio.startListening();

  radio.printDetails();
}
