#include "internet.h"
#include "memory.h"
#include "DF.h"
#include "realClock.h"

int NOA=0, Alarm;
String AT1, AT2, AT3, AT4, AT5, AT6, ML1, ML2, ML3, ML4, ML5, ML6;
unsigned long firstTime;
bool repeat = false, ATD1, ATD2, ATD3, ATD4, ATD5, ATD6;
String preDate;

const int LED1 = 14, LED2 = 27, LED3 = 26, LED4 = 25, LED5 = 32, LED6 = 33;

long repeatTime = 60*1000;

void setup()
  {
    Serial.begin(115200);
    delay(500);
    EEPROM.begin(4095);
        // comment this two line if you want to clear the eeprom memory 
        //** do it for once and again comment these lines otherwise the eeprom will be clear every time you turn on the device
    // for(int i =0; i<=4095; i++) { EEPROM.writeInt(i,0); }
    // EEPROM.commit();

    DF_begin(30, 15); // Initiating DF player Argument1 -- volume(0-30), Argument2 -- microcontrollers pin no. where DF players busy pin is connected
    intro(); // Start up music

    if(connect2wifi() && checkNet()) // if connected to wifi as well as internet
      {
        fetchNsave(); // fetch the data from firebase & save it in EEPROM
        readNstore(); // read the data from EEPROM and load it into variables
        sendInt(dName+"/change", 0); // call back check tag setting 0 at start up 
      }
    else // doesnot get internet connectivity
      {
        readNstore(); // read the data from EEPROM and load it into variables
      }

  }

void loop()
  {
    if(getDate() != preDate) //if new date
      {
        Serial.println("New day");
        ATD1 = false; ATD2 = false; ATD3 = false; ATD4 = false; ATD5 = false; ATD6 = false;
        preDate = getDate();
      }

    String currentTime = getTime(); // get the current time
    //Serial.println("currentTime: "+ currentTime);

         if (currentTime == AT1 && !ATD1)   { medAlert(); medCall(ML1); firstTime = millis(); repeat = true; ATD1 = true; Alarm = 1; }
    else if (currentTime == AT2 && !ATD2)   { medAlert(); medCall(ML2); firstTime = millis(); repeat = true; ATD2 = true; Alarm = 2; }
    else if (currentTime == AT3 && !ATD3)   { medAlert(); medCall(ML3); firstTime = millis(); repeat = true; ATD3 = true; Alarm = 3; }
    else if (currentTime == AT4 && !ATD4)   { medAlert(); medCall(ML4); firstTime = millis(); repeat = true; ATD4 = true; Alarm = 4; }
    else if (currentTime == AT5 && !ATD5)   { medAlert(); medCall(ML5); firstTime = millis(); repeat = true; ATD5 = true; Alarm = 5; }
    else if (currentTime == AT6 && !ATD6)   { medAlert(); medCall(ML6); firstTime = millis(); repeat = true; ATD6 = true; Alarm = 6; }

    if(millis()-firstTime >= repeatTime && repeat)
      {
        reptMED();
             if(Alarm == 1) { medCall(ML1); }
        else if(Alarm == 2) { medCall(ML2); }
        else if(Alarm == 3) { medCall(ML3); }
        else if(Alarm == 4) { medCall(ML4); }
        else if(Alarm == 5) { medCall(ML5); }
        else if(Alarm == 6) { medCall(ML6); }
        repeat = false;
      }

    callBackErr();
    if(callBackLS()) 
      {
        fetchNsave(); 
        EEPROM.commit();
        readNstore();
        sendInt(dName+"/change", 0);
        ATD1 = false; ATD2 = false; ATD3 = false; ATD4 = false; ATD5 = false; ATD6 = false;
      }

  }//loop

//___________________________________________Functions________________________________________________

void fetchNsave()
  {
    for(int i = 1; i<=6; i++)
        {
          String tempTAG = dName+"A"+String(i);
          Serial.println("Fetching data from -- " +tempTAG);
          String ATR = rcvString(tempTAG+"/AT"); //delay(10);
          String MLR = rcvString(tempTAG+"/ML"); //delay(10);
          if(ATR != "" && MLR != "")
            {
              String ATRs = ATR.substring(2, (ATR.length()-2) );
              String MLRs = MLR.substring(2, (MLR.length()-2) );
              saveData((i*10), ATRs);
              saveData((i*100), MLRs);
              EEPROM.commit();
              NOA = NOA+1;
              //delay(1);
            }
        } 
  }

void readNstore()
  {
    for(int i = 1; i<=6; i++)
      {
        Serial.println("Fetching data from EEPROM");
        String d2sAT = getData(i*10);
        String d2sML = getData(i*100);
             if (i == 1) { AT1 = d2sAT; ML1 = d2sML; }
        else if (i == 2) { AT2 = d2sAT; ML2 = d2sML; }
        else if (i == 3) { AT3 = d2sAT; ML3 = d2sML; }
        else if (i == 4) { AT4 = d2sAT; ML4 = d2sML; }
        else if (i == 5) { AT5 = d2sAT; ML5 = d2sML; }
        else if (i == 6) { AT6 = d2sAT; ML6 = d2sML; }
        //delay(1);
      }
    Serial.println("AT1: " + AT1 + " -- ML1: " + ML1 );  
    Serial.println("AT2: " + AT2 + " -- ML2: " + ML2 );  
    Serial.println("AT3: " + AT3 + " -- ML3: " + ML3 );  
    Serial.println("AT4: " + AT4 + " -- ML4: " + ML4 );  
    Serial.println("AT5: " + AT5 + " -- ML5: " + ML5 );  
    Serial.println("AT6: " + AT6 + " -- ML6: " + ML6 );  
  }

void medCall(String medData)
  {
    if(medData.indexOf("1") != -1) { Serial.println("Medicine 1"); digitalWrite(LED1, 1); medVoice1(); }
    if(medData.indexOf("2") != -1) { Serial.println("Medicine 2"); digitalWrite(LED2, 1); medVoice2(); }
    if(medData.indexOf("3") != -1) { Serial.println("Medicine 3"); digitalWrite(LED3, 1); medVoice3(); }
    if(medData.indexOf("4") != -1) { Serial.println("Medicine 4"); digitalWrite(LED4, 1); medVoice4(); }
    if(medData.indexOf("5") != -1) { Serial.println("Medicine 5"); digitalWrite(LED5, 1); medVoice5(); }
    if(medData.indexOf("6") != -1) { Serial.println("Medicine 6"); digitalWrite(LED6, 1); medVoice6(); }
    //delay(30000);
  }
