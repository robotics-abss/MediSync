#include "Arduino.h"
#include "HardwareSerial.h"
#include "DFRobotDFPlayerMini.h"

HardwareSerial mySerial(2);
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
int DFR;

void DF_begin(int vol, int DFpin)
{
  delay(25);
  mySerial.begin(9600);
  DFR = DFpin;
  pinMode(DFR,INPUT);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

    if (!myDFPlayer.begin(mySerial)) 
  {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
   while(true)
   {
     delay(0); // Code to compatible with ESP8266 watch dog.
   }
   Serial.println(F("DFPlayer Mini online."));
   
  }
  
  myDFPlayer.volume(vol);  //Set volume value. From 0 to 30
  delay(1250);
  //myDFPlayer.play(1);  //Play the first mp3
}

//------------------------------------------------

void intro()
{ 
  myDFPlayer.play(13); delay(250); Serial.println("Music No. 13 -- Intro-1");
  while(digitalRead(DFR) == 0)  {  } 
}

void medAlert()
{ 
  myDFPlayer.play(1); delay(250); Serial.println("Music No. 1 -- Intro-2");
  while(digitalRead(DFR) == 0)  {  } 
}

void reptMED()
{ 
  myDFPlayer.play(6); delay(250); Serial.println("Music No. 6 -- card added succesfully");
  while(digitalRead(DFR) == 0)  {  }
}

void medVoice1()
{ 
  myDFPlayer.play(2); delay(250); Serial.println("Music No. 2 --  Connected");
  while(digitalRead(DFR) == 0)  {  } 
}

void medVoice2()
{ 
  myDFPlayer.play(3); delay(250); Serial.println("Music No. 3 -- Not connected");
  while(digitalRead(DFR) == 0)  {  } 
}

void medVoice3()
{ 
  myDFPlayer.play(4); delay(250); Serial.println("Music No. 4 -- Card read mode");
  while(digitalRead(DFR) == 0)  {  } 
}

void medVoice4()
{ 
  myDFPlayer.play(5); delay(250); Serial.println("Music No. 5 -- card add mode");
  while(digitalRead(DFR) == 0)  {  } 
}

void medVoice5()
{ 
  myDFPlayer.play(5); delay(250); Serial.println("Music No. 5 -- card add mode");
  while(digitalRead(DFR) == 0)  {  } 
}

void medVoice6()
{ 
  myDFPlayer.play(5); delay(250); Serial.println("Music No. 5 -- card add mode");
  while(digitalRead(DFR) == 0)  {  } 
}

////////////////////////////////////////////////////////////

void printDetail(uint8_t type, int value)
{
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}