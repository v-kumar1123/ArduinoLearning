//add the servo libary
#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS= Adafruit_MotorShield();
Adafruit_DCMotor *myMotor=AFMS.getMotor(1);

Servo servo1;

int joyX = 0;
int joyY = 1;

int joyValY;
int joyValX;
void setup ()
{
  servo1.attach(10);
  Serial.begin(9600);
  Wire.begin();
  AFMS.begin();
  servo1.write(0);
}

void loop ()
{
  
  joyValY = analogRead(joyY);//Y-Position, will determine motor speed
  myMotor->setSpeed(90);
  servoWrite();
  //Joystick Pushed Forward
  if(joyValY>523){
    //Motor runs forward
    myMotor->run(FORWARD);
  }
  //Joystick at rest, no push backwards or forward
  if(joyValY>501&&joyValY<523){
    //Motor stops
    myMotor->setSpeed(0);
    myMotor->run(RELEASE);
  }
  //Joystick pushed forward
  if(joyValY<501){
    //Motor runs backward
    myMotor->run(BACKWARD);
  }
}
void servoWrite() {
  joyValX = analogRead(joyX);//X-Position, determines servo direction
  joyValX = map(joyValX, 0, 1023, 0, 180); //Maps Joystick value to be from 0 to 180
  servo1.write(joyValX);//Servo direction write
}
