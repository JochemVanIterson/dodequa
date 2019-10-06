#include "SmoothDigital.h"

const int buttonLed1Pin = 3;
const int buttonLed2Pin = 4;
const int buttonLed3Pin = 5;
const int buttonLed4Pin = 6;
const int button1Pin = 14;
const int button2Pin = 15;
const int button3Pin = 16;
const int button4Pin = 17;

SmoothDigital button1;
SmoothDigital button2;
SmoothDigital button3;
SmoothDigital button4;

int button1State;
int button2State;
int button3State;
int button4State;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

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

void loop() {
  // put your main code here, to run repeatedly:
  button1State = button1.read();
  if(button1State != -1) { //button has changed
    if(button1State != 1) digitalWrite(buttonLed1Pin, HIGH);
    else digitalWrite(buttonLed1Pin, HIGH);
  }
  button2State = button2.read();
  if(button2State != -1) { //button has changed
    if(button2State != 1) digitalWrite(buttonLed2Pin, HIGH);
    else digitalWrite(buttonLed2Pin, HIGH);
  }
  button3State = button3.read();
  if(button3State != -1) { //button has changed
    if(button3State != 1) digitalWrite(buttonLed3Pin, HIGH);
    else digitalWrite(buttonLed3Pin, HIGH);
  }
  button4State = button4.read();
  if(button4State != -1) { //button has changed
    if(button4State != 1) digitalWrite(buttonLed4Pin, HIGH);
    else digitalWrite(buttonLed4Pin, HIGH);
  }
}
