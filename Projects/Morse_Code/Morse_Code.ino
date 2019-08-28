#include <Console.h>

char receivedChar;
const byte numChars = 32;
boolean newData = false;
const int ledPin=5;
const int dashs=300;
char observed = 0;
String rec_str="";
const int dots=100;
const int offTime=250;
const int letterSwitch=1000;

/*
 * 
 * delay(offTime);
  digitalWrite(ledPin,HIGH);
  delay(dot);
  digitalWrite(ledPin,LOW);
  
 * */
void setup() {
  
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  
  Serial.println("Please enter what you'd like to say");
  
 recvString();
 
  
}

void loop() {
  recvString();
 showNewData();
  // put your main code here, to run repeatedly:
  static byte counter=0;
  
 //
  //a();
}
boolean dot() {
  delay(offTime);
  digitalWrite(ledPin,HIGH);
  delay(dots);
  digitalWrite(ledPin,LOW);
  
  return true;
}

void determineLetter(){
  //Serial.println("Hetlo");
  if(receivedChar=='a') {
    a();
  }
  if(receivedChar=='b') {
    b();
  }
  if(receivedChar=='c') {
    c();
  }
  if(receivedChar=='d') {
    d();
  }
  if(receivedChar=='e') {
    e();
  }
  if(receivedChar=='f') {
    f();
  }
  if(receivedChar=='g') {
    g();
  }
  if(receivedChar=='h') {
    //Serial.println("CHAR RECEIVED");
    h();
  }if(receivedChar=='i') {
    i();
  }if(receivedChar=='j') {
    j();
  }if(receivedChar=='k') {
    k();
  }if(receivedChar=='l') {
    l();
  }if(receivedChar=='m') {
    m();
  }if(receivedChar=='n') {
    n();
  }if(receivedChar=='o') {
    o();
  }if(receivedChar=='p') {
    p();
  }if(receivedChar=='q') {
    q();
  }if(receivedChar=='r') {
    r();
  }if(receivedChar=='s') {
    s();
  }if(receivedChar=='t') {
    t();
  }if(receivedChar=='u') {
    u();
  }if(receivedChar=='v') {
    v();
  }if(receivedChar=='w') {
    w();
  }if(receivedChar=='x') {
    x();
  }if(receivedChar=='y') {
    y();
  }if(receivedChar=='z') {
    z();
  } 
}

void showNewData() {
  newData = false;
}

void recvOneChar() {
 if (Serial.available() > 0) {
 receivedChar = Serial.read();
 newData = true;
 }
}

//https://startingelectronics.org/software/arduino/learn-to-program-course/19-serial-input/ for source of String input.


void recvString(){
 while(Serial.available()>0) {
  observed=Serial.read();
  if(observed!='\n'){
    rec_str+=observed;
    receivedChar=observed;
    determineLetter();
  }
  else{
    //Serial.println("I HAVE RECEIVED "+rec_str);
   break; 
  }

  
  
 }
 //return rec_str;
 
 newData=true;
}

boolean dash() {
  delay(offTime);
  digitalWrite(ledPin,HIGH);
  delay(dashs);
  digitalWrite(ledPin,LOW);
  
  return true;
}

/*void recvString(){
  static int indx=0;
  receivedChars[indx];
 char finisher='\n';
 char readed;
 while(Serial.available()>0&&newData==false) {
  readed=Serial.read();

  if(readed!=finisher) {
    receivedChars[indx]=readed;
    indx++;

    if(indx>=numChars) {
      indx=numChars-1;
     
    }
  }
  else {
    recievedChars[indx]='\0';
    indx=0;
    newData=true;
  }
 }
}*/

boolean a() {
  dot();
  dash();
  delay(letterSwitch);
  return true;
}

boolean b() {
  dash();
  dot();
  dot();
  dot();
  delay(letterSwitch); 
  return true;
}

boolean c() {
  dash();
  dot();
  dash();
  dot();
  delay(letterSwitch);
  return true;
}

boolean d() {
  dash();
  dot();
  dot();
  
  delay(letterSwitch);
  return true;
  
}

boolean e(){
  dot();
  
  delay(letterSwitch);
  return true;
}

boolean f(){
  dot();
  dot();
  dash();
  dot();

  delay(letterSwitch);
  return true;
}

boolean g(){
  dash();
  dash();
  dot();

  delay(letterSwitch);
  return true;
}

boolean h(){
  dot();
  dot();
  dot();
  dot();

  
  delay(letterSwitch);
  return true;
}

boolean i() {
  dot();
  dot();

  
  delay(letterSwitch);
  return true;
}

boolean j() {
  dot();
  dash();
  dash();
  dash();

  
  delay(letterSwitch);
  return true;
}

boolean k(){
  dash();
  dot();
  dash();
  
  delay(letterSwitch);
  return true;
}

boolean l(){
  dot();
  dash();
  dot();
  dot();
 
  delay(letterSwitch);
  return true;
}

boolean m(){
  dash();
  dash();

  
  delay(letterSwitch);
  return true;
}

boolean n(){
  dash();
  dot();
  
  delay(letterSwitch);
  return true;
}

boolean o() {
  dash();
  dash();
  dash();

 
  delay(letterSwitch);
  return true;
}

boolean p(){
  dot();
  dash();
  dash();
  dot();
  
  delay(letterSwitch);
  return true;
}

boolean q(){
  dash();
  dash();
  dot();
  dash();
  
  delay(letterSwitch);
  return true;
}

boolean r(){
  dot();
  dash();
  dot();
  
  delay(letterSwitch);
  return true;
}

boolean s(){
  dot();
  dot();
  dot();
  
  delay(letterSwitch);
  return true;
}

boolean t(){
  dash();
  
  delay(letterSwitch);
  return true;
}

boolean u(){
  dot();
  dot();
  dash();
  
  delay(letterSwitch);
  return true;
}

boolean v() {
  dot();
  dot();
  dot();
  dash();

 
  delay(letterSwitch);
  return true;
}

boolean w(){
  dot();
  dash();
  dash();
  
  delay(letterSwitch);
  return true;
}

boolean x(){
  dash();
  dot();
  dot();
  dash();
  
  delay(letterSwitch);
  return true;
}

boolean y(){
  dash();
  dot();
  dash();
  dash();

  
  delay(letterSwitch);
  return true;
}

boolean z(){
  dash();
  dash();
  dot();
  dot();
  
  delay(letterSwitch);
  return true;
}
