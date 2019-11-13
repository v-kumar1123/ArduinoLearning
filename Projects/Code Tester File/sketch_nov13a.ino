int carSpeed=99.5;
char message[30]="";//message to send receiver
char* direccion="BACKWARD";
int servoPos=85;
void setup() {
  // put your setup code here, to run once:  
  Serial.begin(9600);//(console initiation)
}

void loop() {
//  char carSpeeds=carSpeed;
//  char servo=servoPos;
//  Serial.println(carSpeed);
//  delay(1000);
//  strcpy(message,direccion);
//  strcat(message,":");
//  message[strlen(direccion)+1]=carSpeed/1+'0';
//  //strcat(message,carSpeed+'0');
//  strcat(message,":");
//  strcat(message,servoPos+'0');
//  Serial.println(message);
    message[0]=carSpeed/10+'0';
    Serial.println(message);
}
