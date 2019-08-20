const int ledPin = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   digitalWrite(ledPin,HIGH);//turn the LED on 
   delay(500);               //wait for half a second
   digitalWrite(ledPin,LOW); //turn the LED off
   delay(500);               //wait for half a second
}
