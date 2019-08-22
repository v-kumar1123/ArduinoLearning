char receivedChar;
const byte numChars = 32;
boolean newData = false;
char receivedChars[numChars];

void setup() {
 Serial.begin(9600);
 Serial.println("<Arduino is ready>");
}

void loop() {
 recvOneChar();
 showNewData();
}

void recvOneChar() {
 if (Serial.available() > 0) {
 receivedChar = Serial.read();
 newData = true;
 }
}

void showNewData() {
 if (newData == true) {
 Serial.print("This just in ... ");
 Serial.println(receivedChar);
 newData = false;
 }
}

void recvWithEndMarker() {
 /*static byte ndx = 0;
 char endMarker = '\n';
 char rc;
 while (Serial.available() > 0 && newData == false) {
 rc = Serial.read();

 if (rc != endMarker) {
 receivedChars[ndx] = rc;
 ndx++;
 if (ndx >= numChars) {
 ndx = numChars - 1;
 }
 }
 else {
 receivedChars[ndx] = '\0'; // terminate the string
 ndx = 0;
 newData = true;
 }
 }*/
 static int indx=0;
 char finisher='\n';
 char readed;

 while(Serial.available>0&&newData==false) {
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
    
  }
 }
 
}
