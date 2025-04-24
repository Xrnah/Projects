/*********************************************
    IoT Weather Station 
    For FDCNLAB ECE221
**********************************************/

/*****************************************************************************************************************
    Objective: The goal of the project is to create an IoT-enabled weather station that monitors environmental 
      factors like temperature, humidity, rainfall, flooding, and pollution using an ESP32 microcontroller. 
      The collected data will be displayed in real-time through the Blynk mobile app, enabling users to 
      remotely track local weather conditions. In the event of severe flooding, an overflow drainage 
      system will be triggered automatically or can be activated remotely. 
******************************************************************************************************************/

  // [Monitor] : [Sensors]
    // Temp & Humidity : DHT11              https://lastminuteengineers.com/dht11-module-arduino-tutorial/
    // Flood : HW-038 Water Level Sensor    https://lastminuteengineers.com/water-level-sensor-arduino-tutorial/
    // Rain : HL-83 Rain Sensor             https://randomnerdtutorials.com/guide-for-rain-sensor-fc-37-or-yl-83-with-arduino/
    // Pollution : MQ135 Air Quality Sensor https://blog.robberg.net/mq-135-arduino/

// Made for esp32 by Espressif Systems: ESP32 Dev Module
// Ver: 0.1.110524.Final.Commented

// Naming Convention:
  // CONSTANTS/DEFINITIONS: MACRO_CASE
  // variables: kebab-case
  // standard_libraries: snake_case
  // functions/constantVariables: camelCase
  // *Common and Proper nouns follow the same convention

// Line length: (columns = cols)
  // Best: 80 cols
  // Used in Arduino: 140 char == 80 tabs

//---------Constants and Definitions:
  #include "_header.h"          // Include user-defined headers with constants and setup
  #include "DEBUG.h"            // Include debugging header for optional debug print statements

//---------Libraries:
  #include <MQUnifiedsensor.h>  // Library for MQ135 air quality sensor
  
  #include <Adafruit_Sensor.h>  // Base library for Adafruit sensors
  #include <DHT.h>              // Library for DHT temperature and humidity sensor
  #include <Adafruit_GFX.h>     // Library for graphics support on the OLED display
  #include <Adafruit_SSD1306.h> // Library for the SSD1306 OLED display

  #include <WiFi.h>             // WiFi library for ESP32
  #include <WiFiClient.h>       // Basic WiFi client library for ESP32
  #include <BlynkSimpleEsp32.h> // Blynk library for ESP32
  #include <TimeLib.h>          // Built-in time library for Blynk

//---------Objects:
  BlynkTimer timer;                     // Creates a timer object for recurring tasks in the Blynk environment
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Initialize OLED display with parameters
  DHT dht(DHTPIN, DHTTYPE);             // Initialize DHT sensor with pin and type
  // MQ135 air quality sensor initialization can be added in the future
  // MQUnifiedsensor MQ135(board, Voltage_Resolution, ADC_Bit_Resolution, AIR_MQ_PIN, MQ_type);
  #include "OLED.h"                     // Include OLED header with display configurations

void setup() {
  //----------------Serial
    DEBUG_SERIAL_BEGIN(115200);                      // Initializes serial monitor for debugging

  //----------------OLED
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        DEBUG_PRINTln(F("SSD1306 allocation failed"));
        for(;;);                                      // Halts execution if OLED initialization fails
    }
    display.display();
    delay(2000);
    display.clearDisplay();                           // Clears OLED buffer for a fresh start

  //----------------Blynk
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);       // Connects ESP32 to Blynk using WiFi credentials

  //----------------DHT
    dht.begin();                                     // Starts the DHT sensor
    
  //----------------MQ135
    /// Configures MQ135 for CO2 measurement (commented out but ready to initialize)
    // Set math model to calculate the PPM concentration and the value of constants
    // MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
    // MQ135.setA(MQ_135_A); MQ135.setB(MQ_135_B); // Configure the equation to to calculate CO2 concentration
    // MQ135.init();
    // MQ135.setRL(MODULE_RL);
    // MQ135.setR0(CALCULATED_R0);
    // MQ135.serialDebug(true);

  //----------------pinMode
    pinMode(FLOOD_HW_PIN, INPUT_PULLDOWN);           // Sets water level sensor pin as input
    pinMode(RAIN_HL_PIN, INPUT_PULLDOWN);            // Sets rain sensor pin as input
    pinMode(RELAY_PIN, OUTPUT);                      // Sets relay pin as output to control the drainage system
    
  //----------------Timers
    timer.setInterval(timerDHTComfort, assessComfortWrapper);  // Periodic comfort assessment
    timer.setInterval(timerAirQuality, readAirPollution);      // Air quality check
    timer.setInterval(timerFlood, waterLevelAverageWrapper);   // Water level monitoring
    timer.setInterval(timerRain, rainCheckWrapper);            // Rain status check

    timer.setInterval(timerBlynkRefresh, blynkRefreshVariables); // Periodic data push to Blynk
    timer.setInterval(timerBlynkRefresh, disconnectedBlynk);    // Check Blynk connection

    timer.setInterval(timerAirQuality, calibrate_R0_MQ135_Wrapper); // Periodic MQ135 calibration
    
}

void loop() {
    // Sensors/Displays
    sensorDHT11(&humidity, &temperature);           // Reads DHT sensor data
    OLED_Display(&temperature, &humidity);          // Updates OLED display with temperature and humidity
    waterPump();                                    // Controls water pump based on water level

    // ESP32
    timer.run();                                    // Runs Blynk timers
    Blynk.run();                                    // Keeps Blynk connection active
    reconnectWiFi();                                // Ensures WiFi connection remains stable
}

