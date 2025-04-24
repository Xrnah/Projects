//------------------------Bluetooth------------------------------//
  //#define USE_PIN         // Uncomment this to use PIN during pairing. The pin is specified on the line below
  const char *pin = "1234"; // Change this to more secure PIN.

  String device_name = "     ECE221     ";

  #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
  #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
  #endif

  #if !defined(CONFIG_BT_SPP_ENABLED)
  #error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
  #endif

  BluetoothSerial SerialBT;

  //-------------------------LCD---------------------------------//
    // set the LCD number of columns and rows
    int lcdColumns = 16;
    int lcdRows = 2;

    // set LCD address, number of columns and rows
    // if you don't know your display address, run an I2C scanner sketch
    LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
    
    enum Status {
      READY_TO_RECEIVE,
      REPLAYING,
      CONNECTED,
      NOT_CONNECTED,
      DISPLAYING,
      RESET
    };

//------------------------IR_Counter-----------------------------//
  const int irSensor1Pin = 39; // Sensor 1 connected to digital pin 7 //Yellow 39=VN
  const int irSensor2Pin = 36; // Sensor 2 connected to digital pin 8 //Orange 36=VP

  volatile int irSensor1State = HIGH;
  volatile int irSensor2State = HIGH;

  volatile bool sensor1Triggered = false;
  volatile bool sensor2Triggered = false;
  volatile bool sensor1TriggeredAfterSensor2 = false;
  volatile bool sensor2TriggeredAfterSensor1 = false;
  volatile int count = 0;

  unsigned long previousMillis_IR = 0;  // Variable to store the last time the function was called
  const int sensorHoldTime = 500;       // This is used to avoid sumultaneous trigger
  const int delayBetweenCounts = 0;     // Time in milliseconds to avoid multiple counts for the same person
  const int IR_reset_time = 2500;       // 2.5 sec time till all flag reset.

//------------------------Relay----------------------------------//
  int AC_Relay_Pin = 13;  // AC_Relay 
  int DC_Relay_Pin = 14;  // DC_Relay

  unsigned long previousMillis_AC = 0;
  int delay_AC = 4500;    // 4.5s delay; 0 delay on diorama;

//------------------------Motor_Control--------------------------//
  //PWM_FAN_Variables
  int PWM_FAN = 33;
  int FAN_SPEED;          //Setting up for case switch
  bool FAN_STATE = true;  //While loop
  unsigned long previousMillis_PWM = 0;

  //----------------------Digital_to_Analog----------------------//
    //Only GPIO 25 and GPIO 26 is DAC capable
    DacESP32 dac1(GPIO_NUM_25);
    float DAC_FAN_S;

//------------------------TEMP-----------------------------------//
  int TEMP_SENS = 34;
  const unsigned interval = 2000;   // 2 seconds * 1000 = millis
  float prev_temp = 0;              // zero for initialization

  