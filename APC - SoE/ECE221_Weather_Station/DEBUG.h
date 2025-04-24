/*
  This file serves as the debugging system for the Weather Station.
  Commenting certain definitions (#define) will trigger macros that will enable/disable prints.
  
  * This file is optional but to retain debugging prints, all defined macros must be replaced ...
    ... back to "Serial.(function)" on each designated line.
*/

//---------Serial
  // This prints foundational processes such as:
    // WiFi connection
    // Internet connection
  #define DEBUG_SERIAL // Comment to turn of all prints, to save space

  #ifdef DEBUG_SERIAL
      #define DEBUG_SERIAL_BEGIN(x) Serial.begin(x)
    #else
      #define DEBUG_SERIAL_BEGIN(x) // Do nothing
  #endif

//---------DEBUG SHORTCUT COMMANDS
  // #define DEBUG_ALL // Uncomment to turn ON all debug prints

  /********************************************************
  Comment DEBUG_ALL and select to filter debug prints below 
  *********************************************************/
  // #define DEBUG_MODE 1   // Main Code Components
  // #define DEBUG_DHT 1    // DHT (Temperature & Humidity)
  // #define DEBUG_AIR 1    // MQ135 (Air Pollution)
  // #define DEBUG_FLOOD 1  // HW-038 (Flood)
  // #define DEBUG_RAIN 1   // HL-83 (Rain)
  // #define DEBUG_PUMP 1   // Relay (Water Pump)
  // #define DEBUG_BLYNK 1  // Blynk


//---------DEBUG MACROS
  #ifdef DEBUG_ALL
      #define DEBUG_MODE    1
      #define DEBUG_DHT     1
      #define DEBUG_AIR     1
      #define DEBUG_FLOOD   1
      #define DEBUG_RAIN    1
      #define DEBUG_PUMP    1
      #define DEBUG_BLYNK   1 
  #endif

  #if DEBUG_MODE
      #define DEBUG_PRINTln(x)        Serial.println(x)
      #define DEBUG_PRINTf(fmt, ...)  Serial.printf((fmt), ##__VA_ARGS__)
    #else
      #define DEBUG_PRINTln(x)          // Do nothing
      #define DEBUG_PRINTf(fmt, ...)    // Do nothing
  #endif

  #if DEBUG_DHT
      #define DEBUG_DHT_PRINTln(x)        Serial.println(x)
      #define DEBUG_DHT_PRINTf(fmt, ...)  Serial.printf((fmt), ##__VA_ARGS__)
    #else
      #define DEBUG_DHT_PRINTln(x)          // Do nothing
      #define DEBUG_DHT_PRINTf(fmt, ...)    // Do nothing
  #endif

  #if DEBUG_AIR
      #define DEBUG_AIR_PRINTln(x)        Serial.println(x)
      #define DEBUG_AIR_PRINTf(fmt, ...)  Serial.printf((fmt), ##__VA_ARGS__)
    #else
      #define DEBUG_AIR_PRINTln(x)          // Do nothing
      #define DEBUG_AIR_PRINTf(fmt, ...)    // Do nothing
  #endif
  
  #if DEBUG_FLOOD
      #define DEBUG_FLOOD_PRINTln(x)        Serial.println(x)
      #define DEBUG_FLOOD_PRINTf(fmt, ...)  Serial.printf((fmt), ##__VA_ARGS__)
    #else
      #define DEBUG_FLOOD_PRINTln(x)          // Do nothing
      #define DEBUG_FLOOD_PRINTf(fmt, ...)    // Do nothing
  #endif

  #if DEBUG_RAIN
      #define DEBUG_RAIN_PRINTln(x)        Serial.println(x)
      #define DEBUG_RAIN_PRINTf(fmt, ...)  Serial.printf((fmt), ##__VA_ARGS__)
    #else
      #define DEBUG_RAIN_PRINTln(x)          // Do nothing
      #define DEBUG_RAIN_PRINTf(fmt, ...)    // Do nothing
  #endif

  #if DEBUG_PUMP
      #define DEBUG_PUMP_PRINTln(x)        Serial.println(x)
      #define DEBUG_PUMP_PRINTf(fmt, ...)  Serial.printf((fmt), ##__VA_ARGS__)
    #else
      #define DEBUG_PUMP_PRINTln(x)          // Do nothing
      #define DEBUG_PUMP_PRINTf(fmt, ...)    // Do nothing
  #endif

  #if DEBUG_BLYNK
      #define DEBUG_BLYNK_PRINTln(x)        Serial.println(x)
      #define DEBUG_BLYNK_PRINTf(fmt, ...)  Serial.printf((fmt), ##__VA_ARGS__)
    #else
      #define DEBUG_BLYNK_PRINTln(x)          // Do nothing
      #define DEBUG_BLYNK_PRINTf(fmt, ...)    // Do nothing
  #endif