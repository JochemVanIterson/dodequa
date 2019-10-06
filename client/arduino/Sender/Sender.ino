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

#include "DodeQuaLED.h"
#include "SmoothAnalog.h"

// ---------------------------------- PINS ---------------------------------- //
const int buttonLed1Pin = 3;
const int buttonLed2Pin = 4;
const int buttonLed3Pin = 5;
const int buttonLed4Pin = 6;
const int button1Pin = 14;
const int button2Pin = 15;
const int button3Pin = 16;
const int button4Pin = 17;

// ----------------------------- DIGITAL INPUTS ----------------------------- //
SmoothDigital button1;
SmoothDigital button2;
SmoothDigital button3;
SmoothDigital button4;
int button1State;
int button2State;
int button3State;
int button4State;

// ---------------------------------- 9DOF ---------------------------------- //
Adafruit_BNO055 bno = Adafruit_BNO055();
SmoothAnalog accSmoother(100);

// ---------------------------- Transceiver vars ---------------------------- //
RF24 radio(7,8);
byte addresses[][6] = {"01Rec","01Sen"};
byte sendableArray[5] = {253, 100, 0, 0, 101};
byte inBytesTrans[5] = {0};

// ------------------------------ TRANSCEIVERS ------------------------------ //
SimpleTransSender transSendAccX;
SimpleTransSender transSendAccY;
SimpleTransSender transSendAccZ;
SimpleTransSender transSendGyroX;
SimpleTransSender transSendGyroY;
SimpleTransSender transSendGyroZ;
SimpleTransSender transSendEulerX;
SimpleTransSender transSendEulerY;
SimpleTransSender transSendEulerZ;
SimpleTransSender transSendButton1;
SimpleTransSender transSendButton2;
SimpleTransSender transSendButton3;
SimpleTransSender transSendButton4;

// ------------------------------- Serial vars ------------------------------ //
byte inBytes[5];
int matchIn[2]  = {101, 251};
int matchOut[2] = {252, 100};
unsigned long lastMillis = 0;

// -------------------------------- SERIALS --------------------------------- //
SimpleSerialSender serialSendAccX;
SimpleSerialSender serialSendAccY;
SimpleSerialSender serialSendAccZ;
SimpleSerialSender serialSendGyroX;
SimpleSerialSender serialSendGyroY;
SimpleSerialSender serialSendGyroZ;
SimpleSerialSender serialSendEulerX;
SimpleSerialSender serialSendEulerY;
SimpleSerialSender serialSendEulerZ;
SimpleSerialSender serialSendButton1;
SimpleSerialSender serialSendButton2;
SimpleSerialSender serialSendButton3;
SimpleSerialSender serialSendButton4;

// -------------------------------- RGB LED --------------------------------- //
DodeQuaLED rgbLed(100);
unsigned long lastPGMChange;
int PGMChangeSpeed = 5000;
int pgmID = 2;

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
  serialSendAccX = SimpleSerialSender(matchOut[0], matchOut[1], 100);
  serialSendAccY = SimpleSerialSender(matchOut[0], matchOut[1], 101);
  serialSendAccZ = SimpleSerialSender(matchOut[0], matchOut[1], 102);
  serialSendGyroX = SimpleSerialSender(matchOut[0], matchOut[1], 110);
  serialSendGyroY = SimpleSerialSender(matchOut[0], matchOut[1], 111);
  serialSendGyroZ = SimpleSerialSender(matchOut[0], matchOut[1], 112);
  serialSendEulerX = SimpleSerialSender(matchOut[0], matchOut[1], 120);
  serialSendEulerY = SimpleSerialSender(matchOut[0], matchOut[1], 121);
  serialSendEulerZ = SimpleSerialSender(matchOut[0], matchOut[1], 122);
  serialSendButton1 = SimpleSerialSender(matchOut[0], matchOut[1], 130);
  serialSendButton2 = SimpleSerialSender(matchOut[0], matchOut[1], 131);
  serialSendButton3 = SimpleSerialSender(matchOut[0], matchOut[1], 132);
  serialSendButton4 = SimpleSerialSender(matchOut[0], matchOut[1], 133);

  // -------------- Init Transceiver ports -------------- //
  transSendAccX = SimpleTransSender(&radio, matchOut[0], matchOut[1], 100);
  transSendAccY = SimpleTransSender(&radio, matchOut[0], matchOut[1], 101);
  transSendAccZ = SimpleTransSender(&radio, matchOut[0], matchOut[1], 102);
  transSendGyroX = SimpleTransSender(&radio, matchOut[0], matchOut[1], 110);
  transSendGyroY = SimpleTransSender(&radio, matchOut[0], matchOut[1], 111);
  transSendGyroZ = SimpleTransSender(&radio, matchOut[0], matchOut[1], 112);
  transSendEulerX = SimpleTransSender(&radio, matchOut[0], matchOut[1], 120);
  transSendEulerY = SimpleTransSender(&radio, matchOut[0], matchOut[1], 121);
  transSendEulerZ = SimpleTransSender(&radio, matchOut[0], matchOut[1], 122);
  transSendButton1 = SimpleTransSender(&radio, matchOut[0], matchOut[1], 130);
  transSendButton2 = SimpleTransSender(&radio, matchOut[0], matchOut[1], 131);
  transSendButton3 = SimpleTransSender(&radio, matchOut[0], matchOut[1], 132);
  transSendButton4 = SimpleTransSender(&radio, matchOut[0], matchOut[1], 133);

  // -------------- Buttons -------------- //
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);
  pinMode(buttonLed1Pin, OUTPUT);
  pinMode(buttonLed2Pin, OUTPUT);
  pinMode(buttonLed3Pin, OUTPUT);
  pinMode(buttonLed4Pin, OUTPUT);

  button1 = SmoothDigital(button1Pin, 2);
  button2 = SmoothDigital(button2Pin, 2);
  button3 = SmoothDigital(button3Pin, 2);
  button4 = SmoothDigital(button4Pin, 2);
}

void loop(void){
  radio.stopListening();

  imu::Vector<3> acc   = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  imu::Vector<3> gyro  = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  // sendSerialData(&acc, &gyro, &euler);
  sendTransceiverData(&acc, &gyro, &euler);

  handleButtons();

  double speed = accSmoother.read(totalAcc(&acc)) + accSmoother.read(totalAcc(&gyro));
  if(speed == 0.) {
    if(pgmID==0) rgbLed.rainbowLEDS();
    else if(pgmID==1) rgbLed.randomLEDS();
    else if(pgmID==2) rgbLed.pulseLEDS();

    if(millis() >= lastPGMChange+PGMChangeSpeed){
      int choice = random(0, 5);
      if(choice==0){
        pgmID = 0;
        rgbLed.initRainbowLEDS(random(5, 30));
      } else if(choice==1){
        pgmID = 1;
        rgbLed.initRandomLEDS(random(200, 1000));
      } else if(choice==2){
        pgmID = 2;
        rgbLed.initPulseLEDS(random(5, 100));
      }
      lastPGMChange = millis();
    }
  }
  else eulerLeds(&euler);
  rgbLed.showLEDS(10);
}

void openTransceiver(){
  SPI.setSCK(13);
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  // radio.setPALevel(RF24_PA_MIN);
  radio.setPALevel(RF24_PA_MAX);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);

  // Start the radio listening for data
  radio.enableDynamicPayloads() ;
  radio.setAutoAck( false ) ;
  radio.powerUp() ;
  radio.startListening();

  radio.printDetails();
}
void sendTransceiverData(imu::Vector<3> *acc, imu::Vector<3> *gyro, imu::Vector<3> *euler){
  transSendAccX.sendFloat(acc->x());
  transSendAccY.sendFloat(acc->y());
  transSendAccZ.sendFloat(acc->z());
  transSendGyroX.sendFloat(gyro->x());
  transSendGyroY.sendFloat(gyro->y());
  transSendGyroZ.sendFloat(gyro->z());
  transSendEulerX.sendFloat(euler->x());
  transSendEulerY.sendFloat(euler->y());
  transSendEulerZ.sendFloat(euler->z());
}
void sendSerialData(imu::Vector<3> *acc, imu::Vector<3> *gyro, imu::Vector<3> *euler){
  serialSendAccX.sendFloat(acc->x());
  serialSendAccY.sendFloat(acc->y());
  serialSendAccZ.sendFloat(acc->z());
  serialSendGyroX.sendFloat(gyro->x());
  serialSendGyroY.sendFloat(gyro->y());
  serialSendGyroZ.sendFloat(gyro->z());
  serialSendEulerX.sendFloat(euler->x());
  serialSendEulerY.sendFloat(euler->y());
  serialSendEulerZ.sendFloat(euler->z());
}

void eulerLeds(imu::Vector<3> *euler){
  int red   = map(euler->x(), 0, 360, 0, 100);
  int green = map(euler->y(), -100, 100, 0, 255);
  int blue  = map(euler->z(), -100, 100, 0, 255);
  rgbLed.setLEDS(red, green, blue);
}
double totalAcc(imu::Vector<3> *acc){
  double x = acc->x();
  double y = acc->y();
  double z = acc->z();
  return sqrt( (x*x) + (y*y) + (z*z) );
}
void handleButtons(){
  // put your main code here, to run repeatedly:
  button1State = button1.read();
  if(button1State != -1) { //button has changed
    if(button1State != 1) digitalWrite(buttonLed1Pin, HIGH);
    else digitalWrite(buttonLed1Pin, HIGH);
    transSendButton1.sendBool(button1State);
  }
  button2State = button2.read();
  if(button2State != -1) { //button has changed
    if(button2State != 1) digitalWrite(buttonLed2Pin, HIGH);
    else digitalWrite(buttonLed2Pin, HIGH);
    transSendButton2.sendBool(button2State);
  }
  button3State = button3.read();
  if(button3State != -1) { //button has changed
    if(button3State != 1) digitalWrite(buttonLed3Pin, HIGH);
    else digitalWrite(buttonLed3Pin, HIGH);
    transSendButton3.sendBool(button3State);
  }
  button4State = button4.read();
  if(button4State != -1) { //button has changed
    if(button4State != 1) digitalWrite(buttonLed4Pin, HIGH);
    else digitalWrite(buttonLed4Pin, HIGH);
    transSendButton4.sendBool(button4State);
  }
}
