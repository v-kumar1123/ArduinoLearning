#include <RH_ASK.h>;
#include <SPI.h>;

RH_ASK Radio(2000,2);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(!Radio.init()){
    Serial.println("NO");
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buf [RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if(Radio.recv(buf,&buflen)){
    int i;
    String text="";
    int j;

  for(int j =0; j<buflen; j++){
    text+=(char)(buf[j]);
  }

  Serial.println(text);
  }
}

//RECEIVER
