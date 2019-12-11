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
Adafruit_DCMotor *turner = AFMS.getMotor(3);


RH_ASK rf_driver;
String text="";
int spd=0;
Servo servo1;
int partCounter=0;
int servoPos=0;
int carSpeed=0;
int joyValY=530;
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
  //myMotor->setSpeed(120);

  speedRead();
  Serial.println(joyValY);

  myMotor->setSpeed(carSpeed);
  if(joyValY>550){
          //motor runs forward
     myMotor->run(FORWARD);
  }
        //joystick at rest, not pushed backwards nor forward
  if(joyValY>501&&joyValY<550){
    //motor stops
    myMotor->setSpeed(0);
    myMotor->run(RELEASE);  
    }
        //joystick pushed backward
    if(joyValY<501){
    //motor runs backward
          myMotor->run(BACKWARD);          
    }
        
  if(rf_driver.recv(buf,&buflen)){
    //myMotor->setSpeed(spd);
    partCounter=0;
    int i;
    int j;//This tells me to which part the program needs to go 
  //if the colon is reached, stop the loop and send the text to the method that will assign the value to the part  
  for(j =0; j<buflen; j++){
    if(buf[j]==':') {
      partCounter++;
      if(partCounter==2) {//driving
        //motorSpeed();
        joyValY=text.toInt();
        
      }
      if(partCounter==3){//turning        
        //int pos=text.toInt();        
        //motorTurner(pos);      
      }
      if(partCounter==1) {
        //motorDirection();
      }
      //partAssigner();//calls method that sets value
      //Serial.println(text);
      
      text="";
      continue;
      
    }
    text+=(char)(buf[j]);
  }
  
  
  //myMotor -> setSpeed(carSpeed);
  }

  delay(5);
}

void speedRead() {
  //joyValY = analogRead(1);//y-position, will determine motor speed
  int speed = map(joyValY, 0, 1023, 0, 150); //maps JoystickY value to be from 0 to 150
  speed = speed - 74; //sets speed value scaled
  speed *= 2; //multiply by 2 to increase speed
  carSpeed = abs(speed); //makes speed value to be defaultly positive
}

void motorTurner(int del) {
  //Serial.println(del+" I AM SAD");
  turner->setSpeed(200);
  if(del>40) {
    turner->run(FORWARD);
    delay(abs(500));
  }
  else if(del<25) {
    
    turner->run(BACKWARD);
    delay(abs(500));
  }
  turner->setSpeed(0);
}

//Tells motor in what direction to move
/*void motorDirection() {
  if(text.indexOf("FORWARD")>=0) {
   myMotor->run(FORWARD); 
   return;
  }
  else if(text.indexOf("BACKWARD")>=0) {
    myMotor->run(BACKWARD);
  }
  else if(text.indexOf("RELEASE")>=0) {
    myMotor->setSpeed(0);
    myMotor->run(RELEASE);
  }
}

//Tells motor at what speed to move 
void motorSpeed() {
  //takes int from speed string
  int speedo=text.toInt();
  myMotor -> setSpeed(speedo);
}

//Tells servo motor what direction to move
void servoAssign() {
  //takes int from servo string
  servoPos=text.toInt();
  
  Serial.println(servoPos);
  
}*/
