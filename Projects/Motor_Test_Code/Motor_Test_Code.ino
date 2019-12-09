#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS= Adafruit_MotorShield();
Adafruit_DCMotor *myMotor=AFMS.getMotor(3);


void setup() {
  // put your setup code here, to run once:
  
  Wire.begin();
  AFMS.begin();//motorshield accessible
  
  //0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

}

void loop() {

 myMotor->setSpeed(250);
  myMotor->run(FORWARD);
  delay(30);
 // delay(2000);

  
 
  delay(2000);

  
  myMotor->setSpeed(00);

  
  delay(2000);
}
