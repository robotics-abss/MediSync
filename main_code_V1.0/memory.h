#include <EEPROM.h>

void saveData(int ADD, String content) // for registering new card
  {
    Serial.print("*Saving in the add: "); Serial.println(ADD);
    EEPROM.writeString(ADD, content);
    EEPROM.commit();
    Serial.print("*Address: ");Serial.print(ADD);
    Serial.print("  *Content: ");Serial.println(EEPROM.readString(ADD));
    Serial.println(F("Data saved successfully"));
  }

String getData(int ADD) 
  {
    String val = EEPROM.readString(ADD);
    Serial.print("*Value read done from add " + String(ADD) +": "); Serial.println(val);
    return val; 
  }