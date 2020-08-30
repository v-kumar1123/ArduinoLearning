//nrf24l01 Init Code
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8); // CE, CSN
const byte address[6] = "00001";


//MotorShield Init Code
#include <Adafruit_MotorShield.h>
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
    //Serial.println(buf);

    uint8_t buflen = sizeof(buf);
    partCounter=0;
    int textSplit=0;

    for(textSplit=0; textSplit<buflen; textSplit++) {
      if(buf[textSplit]=":") {
        partCounter++;
        if(partCounter==2) {
          partCounter=0;
          if(text.toInt()==4) {
            myMotor->setSpeed(0);
            myMotor->run(RELEASE);
          }
          if(text.toInt()==2) {
            myMotor->setSpeed(170);
            myMotor->run(BACKWARD);
          }
          if(text.toInt()==1) {
            myMotor->setSpeed(170);
            myMotor->run(FORWARD);
          }
        }
        if(partCounter==3) {
          partCounter=0;
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
        Serial.println(text);
        text="";
      }
      else{
        text+=(char)(buf[textSplit]);
      }
      Serial.println(text);
      
    }
  }
}
