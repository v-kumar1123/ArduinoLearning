//add the servo libary
#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS= Adafruit_MotorShield();
Adafruit_DCMotor *myMotor=AFMS.getMotor(1);

Servo servo1;

int joyX = 0;//joystick pin for X direction for servos
int joyY = 1;//joystick pin for Y direction for motors

int joyValY;//y-position
int joyValX;//x-position

void setup ()
{
  servo1.attach(10);//servo attachment position (10 due to the motor shield)
  Serial.begin(9600);//serial monitor begin
  Wire.begin();
  AFMS.begin();//motorshield accessible
  servo1.write(0);//servo to 0 position
}

void loop ()
{
  
  joyValY = analogRead(joyY);//y-position, will determine motor speed
  
  int speed= map(joyValY, 0, 1023, 0, 150); //maps JoystickW value to be from 0 to 150
  speed=speed-74;//sets speed value scaled
  speed*=2;//multiply by 2 to increase speed
  speed=abs(speed);//makes speed value to be defaultly positive
  Serial.println(speed);//notifies me of speed
  myMotor->setSpeed(speed);//sets speed of motor to scaled speed
  servoWrite();//sets servo value
  //joystick pushed forward
  if(joyValY>523){
    //motor runs forward
    myMotor->run(FORWARD);
  }
  //joystick at rest, not pushed backwards nor forward
  if(joyValY>501&&joyValY<523){
    //motor stops
    myMotor->setSpeed(0);
    myMotor->run(RELEASE);
  }
  //joystick pushed backward
  if(joyValY<501){
    //motor runs backward
    myMotor->run(BACKWARD);
  }
}
void servoWrite() {
  joyValX = analogRead(joyX);//x-position, determines servo direction
  joyValX = map(joyValX, 0, 1023, 0, 180); //maps Joystick value to be from 0 to 180
  //Serial.println(joyValX);//TEMPORARY- tells what # is made
  servo1.write(joyValX);//servo direction written
}
