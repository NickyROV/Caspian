/********************************************************************
*Author : Nicky Lam
*Date : 09 May 2023
*Description : ROV Control by two 6-channel RC Control (Receiving side)
*Hardware : Arduino MEGA
*Un-pack 12 channel PWM signal form top-side and matching to corresponding thruster and manipulator
*Reference : Example of receiving numbers by Nick Gammon dated 31 March 2012
//https://forum.arduino.cc/t/how-to-send-numbers-from-one-arduino-to-another-using-serial/97066
***********************************************************************
*/
const char startOfNumberDelimiter = '<';
const char endOfNumberDelimiter   = '>';
const char acknowledge ='A';
const char lineFeed = '\n';
int RCValue[12];
int i=0;

void setup () { 
  Serial.begin (115200);
  }
  
void unPackInput () {
  static long receivedNumber = 0;
  byte c = Serial.read ();
  switch (c){
    case endOfNumberDelimiter:  
      RCValue[i]=receivedNumber;  
      //Serial. print (i);              //only in debugging stage
      //Serial.print(" = ");            //only in debugging stage
      //Serial.println (RCValue[i]);    //only in debugging stage
      i+=1;  
    //processNumber (receivedNumber); 
    // fall through to start a new number
    case startOfNumberDelimiter: 
      receivedNumber = 0;               //reset received number
      break;
    case '0' ... '9': 
      receivedNumber *= 10;             //left shift
      receivedNumber += c - '0';
      break;
    case lineFeed:
      //Serial.println("End of Package");   //only in debugging stage
      ROVControl();
    } // end of switch  
  }  // end of unPackInput
  
void loop () {
  //Serial.println(i);
  if (Serial.available ())
    unPackInput ();
   } // end of loop

 void ROVControl(){
   Serial.print(acknowledge);
   i=0;   //reset counter
   //Serial.println("Done data un-pack, move on to control");
   //do something with incoming data
   //Serial.println("Finish Control, ready for next data package");
 }
 
