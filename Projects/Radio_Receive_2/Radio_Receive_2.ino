//This file is for the L293D replacement board

//Imported libraries for NRF24L01 chip


#include <RF24.h>

//Creating a radio object
RF24 radio(9,10); //CE, CSN

//address through which transceivers communicate
const byte address[6] = "00001";

String text="";
int partCounter=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //enables user to print to console
  radio.begin();
  //set the address
  radio.openReadingPipe(0, address);
  //Set module as receiver
  radio.startListening();

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
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
        //THRUST MOTOR
        //7 (WHITE) is forward, 6 (ORANGE)  backward
        partCounter=0;
        int speede=text.toInt();
        if(text.toInt()==4) {//stop
          digitalWrite(6, LOW);
          digitalWrite(7, LOW);
        }
        if(text.toInt()==2) {//backward
          digitalWrite(6, HIGH);
          digitalWrite(7, LOW);
        }
        
        if(text.toInt()==1) {//forward
          digitalWrite(6, LOW);
          digitalWrite(7, HIGH);
        }
      }
      if(partCounter==3) {
        //TURNER MOTOR
        //Port 2 (BLACK) to the left, 3 (BLUE) to the right
        partCounter=0;
        if(text.toInt()==4) {//straight
          digitalWrite(2,0);
          digitalWrite(3,0);          
        }
        if(text.toInt()==1) {//right
          digitalWrite(2,0);
          digitalWrite(3,1);
        }
        
        if(text.toInt()==2) {//left
          digitalWrite(2,1);
          digitalWrite(3,0);
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
