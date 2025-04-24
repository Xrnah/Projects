/*
  This file serves as the definition header for ECE211_Weather_Station

  Each segment is divided by stylized hypens ("//-Name-//").
  The first division is for the physical output.
    // This includes the:
      // Timers to run subprocesses/functions without disrupting the main loop program
      // OLED for displaying info for the sensors
      // Relay for enabling a control element
  The second division is for the sensor inputs
    // The sensors are: 
      // DHT11 or DHT22 for temperature and relative humidity
      // MQ-135 for parts [of gas] per million [parts of air] (ppm), measuring air pollution
      // HW-038 measuring rain drop size
        *with HW-01 comparator to process the rain drop size
      // HL-83 for flood or water level sensor
*/

//-------------------------Output--------------------------//
  //-----------------------Timer---------------------------//
    const long timerDHTComfort = 1000;      // Timer interval for DHT sensor updates
    const long timerAirQuality = 1000;      // Timer interval for air quality updates
    const long timerFlood = 1000;           // Timer interval for flood sensor updates
    const long timerRain = 1000;            // Timer interval for rain sensor updates
    const long timerWiFiReconnect = 1000;   // Timer interval for Wi-Fi reconnection checks
    const long timerBlynkRefresh = 1000;    // Timer interval for refreshing Blynk updates

  //-----------------------Blynk---------------------------//
    // Uncomment to debug Blynk communication
    // #define BLYNK_PRINT Serial

    #define BLYNK_TEMPLATE_ID     "TMPL6sPDFvrf8"   // Blynk template ID
    #define BLYNK_TEMPLATE_NAME   "FDCNLAB Weather Station" // Template name
    #define BLYNK_AUTH_TOKEN      "KTqnQ5BgAe-IPP5OAXhvaV6Fgs8JESPd" // Authentication token

    // Wi-Fi SSID
    char ssid[] = "Mansion 103";  // epic_vivo ; Mansion 103 ; 7/11 ; WiFi-801
    // Wi-Fi password
    char pass[] = "Connection_503";  // epicgamer ; Connection_503 ; Baliwkaba? ; #Ramswifi
    
    unsigned long lastReconnectAttempt = 0; // Tracks last Wi-Fi reconnect attempt
    bool connectedWiFi = false;             // Wi-Fi connection status flag

    int terminalSwitch = -1;       // Variable to store terminal switch status
    int terminalSlider = -1;       // Variable to store terminal slider position

    bool terminalUpdatesOnPrinted = false;  // Prevents repeated messages when updates are ON

  //-----------------------OLED----------------------------//
    #define SCREEN_WIDTH    128    // OLED display width
    #define SCREEN_HEIGHT   64     // OLED display height
    #define OLED_RESET      -1     // OLED reset pin, set to -1 if not connected
    #define SCREEN_ADDRESS  0x3C   // OLED I2C address

  //-----------------------Relay----------------------------//
   #define RELAY_PIN 18               // GPIO pin for relay control

    int relaySwitch = 0;              // Relay switch status
    bool relayIndicator;              // Flag for current relay status
    bool lastRelayIndicator = false;  // Tracks last relay state to detect changes

    String relayStatus;               // Holds string representation of relay status

//-------------------------Sensors-------------------------//
  //-----------------------DHT11---------------------------//
    #define DHTPIN 4        // GPIO pin connected to the DHT data pin
    #define DHTTYPE DHT11   // DHT sensor type (DHT11 or DHT22)

    #define VERY_HIGH_TEMP 39.0   // Threshold for very high temperature (°C)
    #define HIGH_TEMP 35.0        // Threshold for high temperature (°C)
    #define MODERATE_TEMP 30.0    // Threshold for moderate temperature (°C)
    #define ROOM_TEMP 26.0        // Threshold for room temperature (°C)
    #define RH_THRESHOLD 60.0     // Relative humidity threshold (%)

    float humidity, temperature;  // Variables to store humidity and temperature
    int heatIndex;                // Heat index based on temperature and humidity
    bool disconnectedDHT;         // Flag for DHT sensor connection status
    
  //-----------------------MQ135---------------------------//
    #define AIR_MQ_PIN 34         // GPIO pin for MQ-135 air quality sensor

    // The following is a configuration using MQUnifiedsensor library mixed from different sources
    // Can be included soon after further testing and calibration

    // #define board "ESP32"
    // #define Voltage_Resolution 5.0
    // #define MQ_type "MQ-135" // MQ135
    // #define ADC_Bit_Resolution 12 
    // #define RatioMQ135CleanAir 3.6  //RS / R0 = 3.6 ppm  

    // #define MQ_135_A 116.6020682
    // #define MQ_135_B -2.769034857
    // #define MODULE_RL 2 
    // #define CALCULATED_R0 37.0

    // #define MQ135_DEFAULTPPM 399 //default ppm of CO2 for calibration
    // #define MQ135_DEFAULTRO 68550 //default Ro for MQ135_DEFAULTPPM ppm of CO2
    // #define MQ135_SCALINGFACTOR 116.6020682 //CO2 gas value
    // #define MQ135_EXPONENT -2.769034857 //CO2 gas value
    // #define MQ135_MAXRSRO 2.428 //for CO2
    // #define MQ135_MINRSRO 0.358 //for CO2

    // /// Parameters for calculating ppm of CO2 from sensor resistance
    // #define PARA 116.6020682
    // #define PARB 2.769034857

    // /// Parameters to model temperature and humidity dependence
    // #define CORA 0.00035
    // #define CORB 0.02718
    // #define CORC 1.39538
    // #define CORD 0.0018

    // /* Exponential regression:
    // GAS      | a      | b
    // CO       | 605.18 | -3.937  
    // Alcohol  | 77.255 | -3.18 
    // CO2      | 110.47 | -2.862
    // Toluen  | 44.947 | -3.445
    // NH4      | 102.2  | -2.473
    // Aceton  | 34.668 | -3.369 */

    // Threshold values for pollution levels (adjust after calibration)
      #define GOOD_AIR 500                // Good air quality (AQI 0-50)
      #define MODERATE_AIR 800            // Moderate air quality (AQI 51-100)
      #define UNHEALTHY_SENSITIVE 1100    // Unhealthy for sensitive groups (AQI 101-150)
      #define UNHEALTHY_AIR 1400          // Unhealthy air quality (AQI 151-200)
      #define VERY_UNHEALTHY_AIR 1700     // Very unhealthy air quality (AQI 201-300)
      #define HAZARDOUS_AIR 2000          // Hazardous air quality (AQI 301-500)

    int rawAirPollution = -1;           // Holds the raw air pollution value

    bool calibrationActive = false;     // Calibration mode flag
    int timerAirQualityID;              // Stores the timer ID for air quality updates

    String airQuality = "N/A";          // Air quality status as a string

  //-----------------------HW-038--------------------------//
    #define FLOOD_HW_PIN 36        // GPIO pin for flood sensor

    #define FLOOD_EMPTY_THRESHOLD 270  // Threshold for no flooding detected
    #define FLOOD_LOW_THRESHOLD   950  // Threshold for low flood level
    #define FLOOD_HIGH_THRESHOLD 1750  // Threshold for high flood level

    #define NUM_READINGS 10             // Number of readings for averaging
    int readings[NUM_READINGS];         // Array to store flood readings
    int readIndex = 0;                  // Current reading index
    int total = 0;                      // Sum of readings for averaging
    int average = 0;                    // Average flood reading

    String waterStatus;                 // Flood status as a string

  //-----------------------HL-83---------------------------//
    #define RAIN_HL_PIN 35         // GPIO pin for rain sensor

    #define LIGHT_RAIN_THRESHOLD    4095 // ADC value for light rain
    #define MODERATE_RAIN_THRESHOLD 3800 // ADC value for moderate rain; Set as 3500 before
    #define HEAVY_RAIN_THRESHOLD    3500 // ADC value for heavy rain; Set as 2700 before

    int rawRainSensor = -1;         // Stores the raw rain sensor value
    String rainStatus;              // Rain status as a string

// End