/*
   Here's the plan: I'll send a string with the direction, speed, and servo value to the receiver arduino

   The format of the message: "DIRECTION(Forward, Backward, or Straight):SPEED:SERVOVALUE"

   The message will be formatted in this class and will be received in the receiver class, called Radio_Action
*/

//THIS CLASS IS INCOMPLETE. I HAVE NOT BEEN ABLE TO FIX THE CHARACTER ERRORS. I AM WORKING ON THE RECEIVER CLASS, AND WILL BE BACK

#include <RH_ASK.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//add the servo libary
#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <string.h>
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

char *message = "RELEASE:0:0"; //message to send receiver
//Create RF24 Obj
RF24 radio(7, 8);  // CE, CSN

const byte address[6] = "00001";

void setup() {
//  servo1.attach(10);//servo attachment position
//  servo1.write(90);//servo to 0 position
  Serial.begin(9600);//(console initiation)
  
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  radio.begin();
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
}
void loop() {
  messageFormat();
  Serial.println(message);
  //  char __message[sizeof(message)];
  //  message.toCharArray(__message, sizeof(__message));
  radio.write(message/*makes message a byte*/, strlen(message)/*length of the String*/);//sends message to receiver
  delay(5);
}

void messageFormat() {
  //The format of the message: "DIRECTION(Forward, Backward, or Straight):SPEED:SERVOVALUE"
  speedRead();//speed of car, 0-150, sets carSpeed variable to speed
  servoPosition();//gives position of servo, sets servoPos variable to position
  String msg="";

  msg.concat("YEET");
  msg.concat(":");
  msg.concat(carSpeed);
  msg.concat(":");
  msg.concat(servoPos);
  msg.concat(":");
  msg.concat(analogRead(3));
  msg.concat(":");
  msg.concat(analogRead(4));
  msg.concat(":");
  msg.concat(digitalRead(2));
  msg.concat(":");
  char mess[55];

  msg.toCharArray(mess,55);

  message=mess;
  
  return;
}


void directionDetermine() {
  
}

void speedRead() {
  joyValY = analogRead(0);//y-position, will determine motor speed
  if (joyValY > 550) {
    //motor runs forward
    carSpeed=1;
  }
  //joystick at rest, not pushed backwards nor forward
  if (joyValY > 450 && joyValY < 550) {
    //motor stops
    carSpeed = 4;
    
  }
  //joystick pushed backward
  if (joyValY < 100) {
    //motor runs backward
    carSpeed=2;
  }
//  int speed = map(joyValY, 0, 1023, 0, 150); //maps JoystickW value to be from 0 to 150
//  speed = speed - 74; //sets speed value scaled
//  speed *= 2; //multiply by 2 to increase speed
//  carSpeed = abs(speed); //makes speed value to be defaultly positive
//  //itoa(carSpeed, carSpeeder, 10);
//  //return carSpeeder;
}

void servoPosition() {
    joyValX = analogRead(2);//x-position, determines motor delay time
    if (joyValX > 550) {
    //RIGHT
    servoPos=1;
  }
  //joystick at rest, not pushed backwards nor forward
  if (joyValX > 450 && joyValX < 550) {
    //STRAIGHT
    servoPos = 4;
    
    
  }
  if (joyValX < 450) {
    //LEFT
    servoPos=2;
  }
    //return servoPosit;
}
