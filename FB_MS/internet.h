#include <WiFi.h>
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "circuiTician"
#define WIFI_PASSWORD "Pneucis@202028"

// #define WIFI_SSID "subha"
// #define WIFI_PASSWORD "yoboy@234"

#define API_KEY "VLPrU1B4YIm0oDNYanbWLh9UVGUQ3aKGoalxowHS"
#define DATABASE_URL "medisync-2eabe-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

String dName = "MediSync/";

//Define Firebase Data object
FirebaseData fbdo;
FirebaseData fbdo1;

FirebaseAuth auth;
FirebaseConfig config;

String  LocK_StaT;
int LS;

bool connect2wifi()
  {
    unsigned long entryT = millis();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(F("Connecting to Wi-Fi"));

    while  (WiFi.status() != WL_CONNECTED && (millis()-entryT<=9000) )
    { Serial.print(F(".")); delay(300); }

    if(millis()-entryT>3000)
      {
        Serial.println(F("Can not connect to wifi starting in normal mode"));
        return false;
      }
    else
      {
        Serial.println();
        Serial.print(F("Connected with IP: "));
        Serial.println(WiFi.localIP());
        Serial.println();

        Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
        config.api_key = API_KEY;
        config.database_url = DATABASE_URL;
        Firebase.begin(DATABASE_URL, API_KEY);
        Firebase.setDoubleDigits(5);
        
        
        if (!Firebase.beginStream(fbdo1, dName+"change"))
          Serial.printf("stream begin error, %s\n\n", fbdo1.errorReason().c_str());

        return true;
      }
    
  }

bool checkNet()
  {
    Serial.printf("Get string... %s\n", Firebase.getString(fbdo, "zzz") ? fbdo.to<const char *>() : fbdo.errorReason().c_str());
    String SOT = fbdo.errorReason().c_str();
    //Serial.println(SOT);
    if (SOT == "send request failed" || SOT == "not connected") { return false; }
    else { return true; }
  }

bool checkWiFi()
  {
    if(WiFi.status() != WL_CONNECTED) { return false;}
    else{ return true; }
  }

void sendString(String KEY, String VALUE)
  {
    if (Firebase.ready()) 
    {
      Firebase.setString(fbdo, KEY, VALUE);
    }
  }

void sendInt(String KEY, int VALUE)
  {
    if (Firebase.ready()) 
    {
      Firebase.setInt(fbdo, KEY, VALUE);
    }
  }

String rcvString(String KEY)
  {
    String value;
    if(Firebase.ready())
      {
        Serial.printf("Get string... %s\n", Firebase.getString(fbdo, KEY) ? fbdo.to<const char *>() : fbdo.errorReason().c_str());
        value= fbdo.to<const char*>();
        // value= Firebase.getString(fbdo, KEY).to<const char*>();

        Serial.print(F("value: "));
        Serial.println(value);
        return value;
      }
  }

void callBackErr()
  {
    if (!Firebase.readStream(fbdo1))
      Serial.printf("stream read error, %s\n\n", fbdo1.errorReason().c_str());

    if (fbdo1.streamTimeout())
      {
        Serial.println("stream timed out, resuming...\n");

        if (!fbdo1.httpConnected())
        Serial.printf("error code: %d, reason: %s\n\n", fbdo1.httpCode(), fbdo1.errorReason().c_str());
      }
  }
  
bool callBackLS()
  {
    if (Firebase.ready() && fbdo1.streamAvailable()) //sol status change
    {
      LocK_StaT = fbdo1.stringData().c_str();
      LS = (LocK_StaT.substring(2, (LocK_StaT.length()-2) )).toInt();
      Serial.println("LS: " + LocK_StaT);
    }
    if(LS == 1) return true;
    else        return false;

  }


