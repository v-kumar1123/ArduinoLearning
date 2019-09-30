#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS= Adafruit_MotorShield();
Adafruit_DCMotor *myMotor=AFMS.getMotor(2);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AFMS.begin();
  
}
 
void loop() {
  // put your main code here, to run repeatedly:
  
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
}

