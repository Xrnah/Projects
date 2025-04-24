/*********************************************
    Aeroponic Monitoring System 
    For DELX2
**********************************************/
// Made for esp32 by Espressif Systems: ESP32 Dev Module
// Ver: 0.1.DevTest_2         // ESP32 board migration from 2.0.17 to 3.0.2
// Window Sort (Left to Right): _GLOBAL_VARIABLES.h; OLED.h; Aeroponic_SYS.ino; Water_Pump.ino;  
                              // pH_sensor.ino; TDS_sensor.ino; TEMP.ino; WiFi_COM.ino;

// ---------Libraries
  #include <OneWire.h>
  #include <DallasTemperature.h>
  #include <SPI.h>
  #include <Wire.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>
  // #include <ToneESP32.h>          // Tone Library for Buzzer; removed on v3.0.2

  #include "_GLOBAL_VARIABLES.h"  // Custom Library Header
  #include "Notes.h"              // Buzzer notes and assigned frequency
  #include "OLED.h"               // OLED must be declared 

void setup() {
  //----------------Serial
    Serial.begin(115200);
  //----------------OLED
    // initialize the OLED object
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
    }
    display.display();
    delay(2000); // Pause for 2 seconds
    // Clear the buffer.
    display.clearDisplay();
  //----------------TEMP
    temp_sensor.begin();
  //----------------pinMode
    // pH_Sensor
    pinMode(pH_Sensor, INPUT);
    
    // TDS_Sensor
    pinMode(TDS_Sensor, INPUT);

    // Buzzer
    pinMode(BUZZER_PIN, OUTPUT);

    // Water_Pump
    pinMode(Pump_Relay, OUTPUT);

    // OLED Button
    pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  float temperature = TEMP();
  float pH_value = pH();
  float TDS_value = TDS();
  
  OLED_Display(temperature, pH_value, TDS_value);
  Water_Pump(pH_value, TDS_value);
  // float current = Pump_Current();
}
