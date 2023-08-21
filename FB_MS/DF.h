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

void intro1()
{ 
  myDFPlayer.play(13); delay(250); Serial.println("Music No. 13 -- Intro-1");
  while(digitalRead(DFR) == 0)  {  } 
}

void intro2()
{ 
  myDFPlayer.play(1); delay(250); Serial.println("Music No. 1 -- Intro-2");
  while(digitalRead(DFR) == 0)  {  } 
}

void connected()
{ 
  myDFPlayer.play(2); delay(250); Serial.println("Music No. 2 --  Connected");
  while(digitalRead(DFR) == 0)  {  } 
}

void notConnected()
{ 
  myDFPlayer.play(3); delay(250); Serial.println("Music No. 3 -- Not connected");
  while(digitalRead(DFR) == 0)  {  } 
}

void CRM()
{ 
  myDFPlayer.play(4); delay(250); Serial.println("Music No. 4 -- Card read mode");
  while(digitalRead(DFR) == 0)  {  } 
}

void CAM()
{ 
  myDFPlayer.play(5); delay(250); Serial.println("Music No. 5 -- card add mode");
  while(digitalRead(DFR) == 0)  {  } 
}

void cardSuc()
{ 
  myDFPlayer.play(6); delay(250); Serial.println("Music No. 6 -- card added succesfully");
  while(digitalRead(DFR) == 0)  {  }
}

void granted()
{ 
  myDFPlayer.play(7); delay(250); Serial.println("Music No. 7 -- access granted");
  while(digitalRead(DFR) == 0)  {  }
}

void denied()
{ 
  myDFPlayer.play(8); delay(250); Serial.println("Music No. 8 -- access denied");
  while(digitalRead(DFR) == 0)  {  }
}

void revoked()
{ 
  myDFPlayer.play(9); delay(250); Serial.println("Music No. 9 -- access revoked");
  while(digitalRead(DFR) == 0)  {  }
}

void opening()
{ 
  myDFPlayer.play(10); delay(250); Serial.println("Music No. 10 -- gate opening");
  //while(digitalRead(DFR) == 0)  {  }
}

void noEnter()
{ 
  myDFPlayer.play(11); delay(250); Serial.println("Music No. 11 -- can not enter");
  while(digitalRead(DFR) == 0)  {  }
}

void alert()
{ 
  while(1)
  {
  myDFPlayer.play(12); delay(250); Serial.println("Music No. 12 -- Security Britch");
  while(digitalRead(DFR) == 0)  {  } 
  delay(1000); break;
  }
}

void add_cancel()
{ 
  myDFPlayer.play(14); delay(250); Serial.println("Music No. 14 -- Card adding process is cancelled");
  while(digitalRead(DFR) == 0)  {  } 
}

void exist()
{ 
  myDFPlayer.play(15); delay(250); Serial.println("Music No. 15 -- Card already exist");
  while(digitalRead(DFR) == 0)  {  } 
}

void wifi_noNet()
{ 
  myDFPlayer.play(16); delay(250); Serial.println("Music No. 16 --  Wifi does not have internet");
  while(digitalRead(DFR) == 0)  {  } 
}

void online()
{ 
  myDFPlayer.play(17); delay(250); Serial.println("Music No. 17 -- starting in online mode");
  while(digitalRead(DFR) == 0)  {  } 
}

void offline()
{ 
  myDFPlayer.play(18); delay(250); Serial.println("Music No. 18 -- starting in offline mode");
  while(digitalRead(DFR) == 0)  {  } 
}

void gain_wifi()
{ 
  myDFPlayer.play(19); delay(250); Serial.println("Music No. 19 -- wifi gained");
  while(digitalRead(DFR) == 0)  {  } 
}

void lost_wifi()
{ 
  myDFPlayer.play(20); delay(250); Serial.println("Music No. 20 -- wifi lost");
  while(digitalRead(DFR) == 0)  {  }
}

void gain_net()
{ 
  myDFPlayer.play(21); delay(250); Serial.println("Music No. 21 -- internet gained");
  while(digitalRead(DFR) == 0)  {  }
}

void lost_net()
{ 
  myDFPlayer.play(22); delay(250); Serial.println("Music No. 22 -- internet lost");
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