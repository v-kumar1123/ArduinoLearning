const int ledPin = 5;
void setup()
{
  pinMode(ledPin,OUTPUT);//initialize the digital pin as an output
}
void loop()
{
  Serial.print(HIGH);
  //turn the LED on 
  delay(100);               //wait for half a second
  digitalWrite(ledPin,LOW); //turn the LED off
  delay(100);               //wait for half a second
}
