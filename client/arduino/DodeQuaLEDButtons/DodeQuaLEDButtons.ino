#include "SmoothDigital.h"

#define led1Pin 3
#define led2Pin 4
#define led3Pin 5
#define led4Pin 6
#define button1Pin 14
#define button2Pin 15
#define button3Pin 16
#define button4Pin 17

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
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);

  button1 = SmoothDigital(button1Pin, 2);
  button2 = SmoothDigital(button2Pin, 2);
  button3 = SmoothDigital(button3Pin, 2);
  button4 = SmoothDigital(button4Pin, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  button1State = button1.read();
  if(button1State != -1) { //button has changed
    if(button1State != 1) digitalWrite(led1Pin, HIGH);
    else digitalWrite(led1Pin, HIGH);
  }
  button2State = button2.read();
  if(button2State != -1) { //button has changed
    if(button2State != 1) digitalWrite(led2Pin, HIGH);
    else digitalWrite(led2Pin, HIGH);
  }
  button3State = button3.read();
  if(button3State != -1) { //button has changed
    if(button3State != 1) digitalWrite(led3Pin, HIGH);
    else digitalWrite(led3Pin, HIGH);
  }
  button4State = button4.read();
  if(button4State != -1) { //button has changed
    if(button4State != 1) digitalWrite(led4Pin, HIGH);
    else digitalWrite(led4Pin, HIGH);
  }
}
