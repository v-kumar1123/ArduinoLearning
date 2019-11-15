/*
   Here's the plan: I'll send a string with the direction, speed, and servo value to the receiver arduino

   The format of the message: "DIRECTION(Forward, Backward, or Straight):SPEED:SERVOVALUE"

   The message will be formatted in this class and will be received in the receiver class, called Radio_Action
*/
#include <RH_ASK.h>
#include <SPI.h>
//add the servo libary
#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

Servo servo1;

int joyX = 0;//joystick pin for X direction for servos
int joyY = 1;//joystick pin for Y direction for motors, joystick 2 plugs in here

int joyValY;//y-position
int joyValX;//x-position
int servoPos;
int carSpeed;
String direccion = "";

char message[30] = "RELEASE:0:0"; //message to send receiver
//Create Amplitude Shift Keying Object
RH_ASK Radio(2000,"", 2);

void setup() {
  servo1.attach(10);//servo attachment position
  servo1.write(90);//servo to 0 position
  Serial.begin(9600);//(console initiation)
  if (!Radio.init()) {
    Serial.println("FAILED!!");
  }
}
void loop() {
  messageFormat();
  //  char __message[sizeof(message)];
  //  message.toCharArray(__message, sizeof(__message));
//  Radio.send((uint8_t/*byte*/ *)message/*makes message a byte*/, strlen(message)/*length of the String*/);//sends message to receiver
//  Radio.waitPacketSent();
  delay(5);
}

void messageFormat() {
  //The format of the message: "DIRECTION(Forward, Backward, or Straight):SPEED:SERVOVALUE"
  speedRead();//speed of car, 0-150, sets carSpeed variable to speed
  char *direccion = directionDetermine(); //says which way car should drive
  servoPosition();//gives position of servo, sets servoPos variable to position

  strcpy(message, direccion);
  strcat(message, ":");
  message[strlen(direccion) + 1] = carSpeed + '0';
  //  strcat(message,":");
  //  strcat(message,servoPos+"");


  return;

}

char *directionDetermine() {
  if (joyValY > 523) {
    //motor runs forward
    return "FORWARD";
  }
  //joystick at rest, not pushed backwards nor forward
  if (joyValY > 501 && joyValY < 523) {
    //motor stops
    carSpeed = 0;
    return "RELEASE";
  }
  //joystick pushed backward
  if (joyValY < 501) {
    //motor runs backward
    return "BACKWARD";
  }
}

void speedRead() {
  joyValY = analogRead(joyY);//y-position, will determine motor speed
  int speed = map(joyValY, 0, 1023, 0, 90); //maps JoystickW value to be from 0 to 150
  speed = speed - 74; //sets speed value scaled
  speed *= 2; //multiply by 2 to increase speed
  carSpeed = abs(speed); //makes speed value to be defaultly positive
  carSpeed = carSpeed / 10;
}

void servoPosition() {
    joyValX = analogRead(joyX);//x-position, determines servo direction
    joyValX = map(joyValX, 0, 1023, 0, 180); //maps Joystick value to be from 0 to 180
    servoPos=joyValX;
}
