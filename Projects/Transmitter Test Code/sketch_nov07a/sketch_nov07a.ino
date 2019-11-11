// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK Radio(2000,"",2);
 
void setup()
{
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  if(!Radio.init()){
    Serial.println("BEUH");
  }
}
 
void loop()
{
  const char *msg="HEY";

  Radio.send((uint8_t *)msg, strlen(msg));
  Radio.waitPacketSent();
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
}


//TRANSMITTER
