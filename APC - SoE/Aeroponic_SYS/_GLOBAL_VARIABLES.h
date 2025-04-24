//------------------------Water_Pump-----------------------------//
  #define Pump_Relay 2
  #define samplingInterval_motor 3
  #define printInterval_motor 800
  //----------------------Buzzer---------------------------------//
    #define BUZZER_PIN 4
    #define BUZZER_CHANNEL 0  // ESP32 = 16 channel max
    
    // ---------- ESP32 3.0.2 migration code (ToneESP32 Lib)
      #define PWM_Res   8
      #define BUZZER_FREQ 2000

      class ToneESP32 { 
        private:
          uint8_t pin; 
          uint32_t freq;
          uint8_t resolution;
          uint8_t channel;
        public:    
          ToneESP32(uint8_t pin, uint32_t freq, uint8_t resolution, uint8_t channel);      
          void tone(int note, int duree);
          void noTone();    
      };

      ToneESP32::ToneESP32(uint8_t pin, uint32_t freq, uint8_t resolution, uint8_t channel) {	
        this->pin = pin;
        this->freq = freq;
        this->resolution = resolution;
        this->channel = channel;
      }

      void ToneESP32::tone(int note, int duree ) {     
        ledcAttachChannel( pin, note, resolution, channel);
        ledcWriteTone( pin, note );                            
          delay(duree);
          ledcWriteTone( pin, 0 );
      }

      void ToneESP32::noTone() {
          ledcDetach(pin);
          ledcWriteTone(pin, 0);
      }

    ToneESP32 buzzer(BUZZER_PIN, 0, PWM_Res, BUZZER_CHANNEL); // buzzer 1

//------------------------pH_Sensor------------------------------//
  #define pH_Sensor 36
  #define Offset 0.00          // deviation compensate; Calibrated through a buffer solution
  #define samplingInterval 20
  #define printInterval 800
  #define ArrayLenth  40       // times of collection; Less = faster value change

  #define min_pH_value  5.5
  #define max_pH_value  6.5

  int pHArray[ArrayLenth];     // Store the average value of the sensor feedback
  int pHArrayIndex=0;

//------------------------TDS_Sensor-----------------------------//
  #define TDS_Sensor 39
  #define VREF 3.3             // analog reference voltage(Volt) of the ADC
  #define SCOUNT  30           // sum of sample point

  #define min_tds_value  450.0
  #define max_tds_value  780.0

  int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
  int analogBufferTemp[SCOUNT];
  int analogBufferIndex = 0, copyIndex = 0;
  float averageVoltage = 0, temperature = 25; // temperature is initially set to 25 (if sensor is not connected, temperature == -127.0)
  float tdsValue = 0;

//------------------------OLED-----------------------------------//
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 64
  #define OLED_RESET     -1
  #define SCREEN_ADDRESS 0x3C

  #define BUTTON_PIN 19
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  
//------------------------TEMP-----------------------------------//
  #define ONE_WIRE_BUS 23 
  float prev_temp = 0;

  OneWire oneWire(ONE_WIRE_BUS);
  DallasTemperature temp_sensor(&oneWire);

//------------------------Blynk_Wi-Fi----------------------------//


