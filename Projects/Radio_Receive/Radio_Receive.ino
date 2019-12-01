#include <Adafruit_MotorShield.h>

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

RH_ASK Radio(2000,2);
String text="";

Servo servo1;
int partCounter=0;


//THIS CLASS IS MADE TO RECEIVE DATA FROM THE TRANSMITTER AND CONVEY TO THE MOTORS AND STUFF....really formal language here amirite?


 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(!Radio.init()) {
    Serial.println("DID NOT INIT CORRECTLY");
  }
  servo1.attach(10);//servo attachment position (10 due to the motor shield)
  Wire.begin();
  AFMS.begin();//motorshield accessible
  servo1.write(0);//servo to 0 position
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buf [RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if(Radio.recv(buf,&buflen)){
    int i;
    j;
    partCounter=0;//This tells me to which part the program needs to go 

  //if the colon is reached, stop the loop and send the text to the method that will assign the value to the part  
  for(j =0; j<buflen; j++){
    if(buf[j]==':') {
      partCounter++;
      partAssigner();//calls method that sets value
      text="";
      continue;
      
    }
    text+=(char)(buf[j]);
  }
  //Serial.println(text);
  }
}

void partAssigner() {
  if(partCounter==0) {
      motorDirection();
  }
  else if(partCounter==1) {
      motorSpeed();
  }  
  else if(partCounter==2) {
      servoAssign();
  }
}

//Tells motor in what direction to move
void motorDirection() {
  if(text.indexOf("FORWARD")>=0) {
    //runs forward    
    myMotor->run(FORWARD);
  }
  else if(text.indexOf("BACKWARD")>=0) {
    //runs backward
    myMotor->run(BACKWARD);
  }
  else if(text.indexOf("RELEASE")>=0) {
    //motor stops, set speed to 0
    myMotor->setSpeed(0);    
    myMotor->run(RELEASE);
  }
}

//Tells motor at what speed to move 
void motorSpeed() {
  //takes int from speed string
  int carSpeed=text.parseInt();
  myMotor -> setSpeed(carSpeed);
}

//Tells servo motor what direction to move
void servoAssign() {
  //takes int from servo string
  int servoPos=text.parseInt();
  servo.write(servoPos);
  
}
