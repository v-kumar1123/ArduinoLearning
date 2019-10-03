#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS= Adafruit_MotorShield();
Adafruit_DCMotor *myMotor=AFMS.getMotor(1);
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Wire.begin();
  AFMS.begin();
  
  myMotor->setSpeed(0);
 
}
 
void loop() {
  // put your main code here, to run repeatedly:
   
  // myMotor->run(FORWARD);
  // delay(5000);
  // myMotor->run(BACKWARD);
  // delay(5000);
}

