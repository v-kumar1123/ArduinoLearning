const int ledPin=5;
const int dash=3000;
const int dot=1000;
const int offTime=1500;
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
}

void loop() {
  // put your main code here, to run repeatedly:

}

void a() {
  dot();
  dash();
}

void b() {
  
}

void dot() {
  delay(offTime);
  digitalWrite(ledPin,HIGH);
  delay(dot);
  digitalWrite(ledPin,LOW);
}

void dash() {
  delay(offTime);
  digitalWrite(ledPin,HIGH);
  delay(dash);
  digitalWrite(ledPin,LOW);
}

void c() {
  
}
