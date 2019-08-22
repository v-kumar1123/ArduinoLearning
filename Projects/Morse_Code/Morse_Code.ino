#include <Console.h>

const int ledPin=5;
const int dashs=1500;
const int dots=500;
const int offTime=1000;
const int letterSwitch=3000;

/*
 * 
 * delay(offTime);
  digitalWrite(ledPin,HIGH);
  delay(dot);
  digitalWrite(ledPin,LOW);
  
 * */
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Console.println("Please enter what you'd like to say");
  String s=Console.readString();
  a();
}

boolean a() {
  dot();
  dash();
  return true;
}

boolean b() {
  
  return true;
}

boolean dot() {
  delay(offTime);
  digitalWrite(ledPin,HIGH);
  delay(dots);
  digitalWrite(ledPin,LOW);
  
  return true;
}

boolean dash() {
  delay(offTime);
  digitalWrite(ledPin,HIGH);
  delay(dashs);
  digitalWrite(ledPin,LOW);
  
  return true;
}

boolean c() {
  
  return true;
}
