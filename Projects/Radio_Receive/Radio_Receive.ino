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

RH_ASK rf_driver;
String text="";
int spd;
Servo servo1;
int partCounter=0;
int servoPos=0;
int carSpeed=0;
boolean forward=false;

boolean backward=false;

boolean stops=false;

//THIS CLASS IS MADE TO RECEIVE DATA FROM THE TRANSMITTER AND CONVEY TO THE MOTORS AND STUFF....really formal language here amirite?


 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rf_driver.init();
  servo1.attach(10);//servo attachment position (10 due to the motor shield)
  Wire.begin();
  AFMS.begin();//motorshield accessible
//  servo1.write(75);
//  delay(5000);
//  servo1.write(120);
  servo1.write(90);//servo to 0 position
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buf [RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  myMotor->setSpeed(spd);

  if(forward){
    myMotor->run(FORWARD);
  }
  else if(backward) {
    myMotor->run(BACKWARD);
  }
  else if(stops){
    myMotor->run(RELEASE);
  }
  

  if(rf_driver.recv(buf,&buflen)){
    
    
  
    partCounter=0;
    int i;
    int j;//This tells me to which part the program needs to go 

  //if the colon is reached, stop the loop and send the text to the method that will assign the value to the part  
  for(j =0; j<buflen; j++){
    if(buf[j]==':') {
      partCounter++;
      if(partCounter==2){        
        int pos=text.toInt();
        servo1.write(pos);        
      //Serial.println(pos);
      }
      if(partCounter==1){        
        spd=text.toInt();
        //delay(5);
        Serial.println(spd);
      }
      if(partCounter==3) {
        motorDirection();
      }
      partAssigner();//calls method that sets value
      //Serial.println(text);
      text="";
      continue;
      
    }
    text+=(char)(buf[j]);
  }
  
  
  myMotor -> setSpeed(carSpeed);
  }

  //delay(5);
}

void partAssigner() {
  if(partCounter==3) {
      motorDirection();
  }
  else if(partCounter==2) {
      //motorSpeed();
  }  
  else if(partCounter==1) {
      //servoAssign();
  }
}

//Tells motor in what direction to move
void motorDirection() {
  if(text.indexOf("FORWARD")>=0) {
    //runs forward    
    forward=true;
    backward=false;
    stops=false;
  }
  else if(text.indexOf("BACKWARD")>=0) {
    //runs backward
    forward=false;
    backward=true;
    stops=false;
  }
  else if(text.indexOf("RELEASE")>=0) {
    //motor stops, set speed to 0
    myMotor->setSpeed(0); 
    forward=false;
    backward=false;
    stops=true;
  }
}

//Tells motor at what speed to move 
void motorSpeed() {
  //takes int from speed string
  carSpeed=text.toInt();
}

//Tells servo motor what direction to move
void servoAssign() {
  //takes int from servo string
  servoPos=text.toInt();
  
  Serial.println(servoPos);
  
}
