#include <Wire.h>;
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//nrf24l01 Init Code
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Arduino.h>

RF24 radio(7,8); // CE, CSN
const byte address[6] = "00001";


//MotorShield Init Code
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *turner = AFMS.getMotor(4);

//Variable Decs
int partCounter=0;
String text="";


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);

  radio.startListening();
  

  
}

void loop() {
  if (radio.available()) {
    char buf[32] = {0};
    radio.read(&buf, sizeof(buf));
    Serial.println(buf);
    /*String thrustD ="";
    thrustD+=(char)(buf[0]);
    
    Serial.println(thrustD);
    thrust(thrustD);
    //turn(""+buf[2]);*/
  }
}

void thrust(String text) {
  if(text.toInt()==4) {
    myMotor->run(RELEASE);
  }
  if(text.toInt()==2) {
    myMotor->run(BACKWARD);
  }
  if(text.toInt()==1) {
    Serial.println("FORWARD");
    myMotor->run(FORWARD);
  }  
}

void turn(String text) {
  if(text.toInt()==4) {
    turner->run(RELEASE);
  }
  if(text.toInt()==1) {
    turner->run(FORWARD);
  }
  if(text.toInt()==2) {  
    turner->run(BACKWARD);
  }
}
