#include <Adafruit_MotorShield.h>

#include <RH_ASK.h>
#include <SPI.h>
//add the servo libary
#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *turner = AFMS.getMotor(4);


//create an RF24 object
RF24 radio(10, 9);  // CE, CSN; according to https://create.arduino.cc/projecthub/muhammad-aqib/nrf24l01-interfacing-with-arduino-wireless-communication-0c13d4

//address through which two modules communicate.
const byte address[6] = "00001";

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

  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();
  //rf_driver.init();
  //servo1.attach(10);//servo attachment position (10 due to the motor shield)
  Wire.begin();
  AFMS.begin();//motorshield accessible
//  servo1.write(75);
//  delay(5000);
//  servo1.write(120);
  servo1.write(90);//servo to 0 position
  
  turner->setSpeed(200);//turn speed to 200
  myMotor->setSpeed(170);
}
void loop() {
  // put your main code here, to run repeatedly:
    
  

  if(radio.available()){
    char buf[32] = {0};
    radio.read(&buf, sizeof(buf));
    Serial.println(buf);

    
  uint8_t buflen = sizeof(buf);
    //myMotor->setSpeed(spd);
    partCounter=0;
    int j;//This tells me to which part the program needs to go 
  //if the colon is reached, stop the loop and send the text to the method that will assign the value to the part  
  for(j =0; j<buflen; j++){
    if(buf[j]==':') {
      partCounter++;
      //1st carSpeed, 2nd turner
      if(partCounter==2) {
        partCounter=0;
        int speede=text.toInt();
        if(text.toInt()==4) {
          stopp();
        }
        if(text.toInt()==2) {
          myMotor->setSpeed(100);
          myMotor->run(BACKWARD);
        }
        
        if(text.toInt()==1) {
          forwardd();
        }
      }
      if(partCounter==3) {
        partCounter=0;
        //Serial.println("TURNER"+text.toInt());
        if(text.toInt()==4) {
          turner->run(RELEASE);
        }
        if(text.toInt()==1) {
          Serial.println("OMG");
          turner->run(FORWARD);
        }
        
        if(text.toInt()==2) {
          turner->run(BACKWARD);
        }
      }
      
      
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
void stopp() {
  myMotor->setSpeed(0);
  myMotor->run(RELEASE);
}
void forwardd() {
  myMotor->setSpeed(100);
  myMotor->run(FORWARD);
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
