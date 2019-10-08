#include <Servo.h>
// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
Servo servo;

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
  servo.attach(12);
  servo.write(90);
}

void loop() {
  int x= analogRead(X_pin);
  int y= analogRead(Y_pin);

  int valX = map(x, 1023, 0, 10, 170);
  int valY = map(y, 0, 1023, 10, 170);
  servo.write(valX);

  delay(5);

  /*if(x==522){
    servo.write(90);
  }
  if(x>523) {
    Serial.println("Right");
    servo.write(180);
  }
  if(x<521){
    Serial.println("Left:");
    servo.write(250);
  }
  if(y>509) {
    Serial.println("Backward");
  }
  if(y<505){
    Serial.println("Forward");
  }*/
}
