/*************************************************************************************
 *Author : Nicky Lam 
 *Date : 09 May 2023
 *Description : ROV control by two 6-channel RC Control (Transmitting side)
 *Hardware : Arduino MEGA
 *Radio Control 1 : 6 Channel (ROV)
 *RC1C1-Sway, RC1C2-Surge, RC1C3-Heave, RC1C4-Yaw, RC1C5-LED, RC1C6-Middle Claw
 *Radio Control 2 : 6 Channel (Manipulator)
 *RC2C1-Right, RC2C2-Right, RC2C3-Left, RC2C4-Left, RC2C5-Right-apply, RC2C6-Left-apply
 *All Channel should be connect properly or disable, pulseIn(open end) drag on the program 
 **************************************************************************************
 */
#define RC1Channel1 22   //Sway
#define RC1Channel2 24   //Surge
#define RC1Channel3 26   //Heave
#define RC1Channel4 28   //Yaw
#define RC1Channel5 30   //LED On/Off
#define RC1Channel6 32   //Middle Claw

#define RC2Channel1 34   //Right Manipulator
#define RC2Channel2 36   //Right Manipulator
#define RC2Channel3 38  //Right Manipulator
#define RC2Channel4 40  //Left Manipulator
#define RC2Channel5 42  //Left Manipulator
#define RC2Channel6 44  //Left Manipulator

#define RCValueCheckPin 12    //Data receive from RC value check
#define ackPin 13             //Data package receive from far side acknowledge
const char acknowledge = 'A';

//Data Package Format <RC1C1><RC1C2><RC1C3>..............<RC2C4><RC2C5><RC2C6>+Carriage return+Line Feed
const char startOfNumberDelimiter = '<';
const char endOfNumberDelimiter   = '>';
int RCValue[12];
bool RCValueCheck = false;

void setup() {
  Serial.begin(115200);
  pinMode(RC1Channel1, INPUT);
  pinMode(RC1Channel2, INPUT);
  pinMode(RC1Channel3, INPUT);
  pinMode(RC1Channel4, INPUT);
  pinMode(RC1Channel5, INPUT);
  pinMode(RC1Channel6, INPUT);
  pinMode(RC2Channel1, INPUT);
  pinMode(RC2Channel2, INPUT);
  pinMode(RC2Channel3, INPUT);
  pinMode(RC2Channel4, INPUT);
  pinMode(RC2Channel5, INPUT);
  pinMode(RC2Channel6, INPUT);
  pinMode(RCValueCheckPin, OUTPUT);
  pinMode(ackPin, OUTPUT);
}



void loop() {
  //Reading Cycle
  RCValue[0]=pulseIn(RC1Channel1, HIGH);
  RCValue[1]=pulseIn(RC1Channel2, HIGH);
  RCValue[2]=pulseIn(RC1Channel3, HIGH);
  RCValue[3]=pulseIn(RC1Channel4, HIGH);
  RCValue[4]=pulseIn(RC1Channel5, HIGH);
  RCValue[5]=pulseIn(RC1Channel6, HIGH);
  RCValue[6]=pulseIn(RC2Channel1, HIGH);
  RCValue[7]=pulseIn(RC2Channel2, HIGH);
  RCValue[8]=pulseIn(RC2Channel3, HIGH);
  RCValue[9]=pulseIn(RC2Channel4, HIGH);
  RCValue[10]=pulseIn(RC2Channel5, HIGH);
  RCValue[11]=pulseIn(RC2Channel6, HIGH);
  if (RCValue[0]>0 & RCValue[6]>0){
    RCValueCheck = true;
  } else {
    RCValueCheck = false;
  }
  
  
  //Serial Print to UART Cycle
  for (int i=0; i<12; i++){
    
    Serial.print (startOfNumberDelimiter);    //Open Bracket
    Serial.print (RCValue[i]);                 //RC Value
    Serial.print (endOfNumberDelimiter);      //Close Bracket
  }
    Serial.write(13);         //Carriage Return
    Serial.write(10);         //Line feed
    delay (1000);

  //Radio Control value receive status check
    if (RCValueCheck){
      digitalWrite(RCValueCheckPin, HIGH);
    } else {
      digitalWrite(RCValueCheckPin, LOW);
    }
    
  //Data package receive status check 
    byte c = Serial.read();
    if (c==acknowledge){               //Acknowledge character
      digitalWrite(ackPin, HIGH);
    } else {
      digitalWrite(ackPin, LOW);
    }
    
}  // end of loop
