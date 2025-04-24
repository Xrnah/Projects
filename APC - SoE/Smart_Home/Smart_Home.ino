/*********************************************
    FINAL CODE for Diorama (Overall System)
      For DELX1 and ELEX3
**********************************************/
// Made for esp32 by Espressif Systems: ESP32 Dev Module
// Ver: Revision.1_Clean_NoTempPWM
// Window Sort (Left to Right): _GLOBAL_VARIABLES.h; FINAL_CODE.ino; BT_LCD.ino; IR_Counter.ino; 
                              // FAN_MOTOR_INPUT.ino; TEMP_PWM_DAC.ino; WiFi_LOG.ino; Relay.ino;

#include "BluetoothSerial.h"    // Bluetooth Interfacing
#include <LiquidCrystal_I2C.h>  // LCD_I2C
#include <DacESP32.h>           // Digital to Analog Output for analogRead() on Shield

#include "_GLOBAL_VARIABLES.h"  // Custom Library Header

void setup() {
  //----------------Serial
    Serial.begin(115200);
  //----------------LCD
    // initialize LCD
    lcd.init();
    // turn on LCD backlight                      
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print(device_name); // Limit to 16 char

  //----------------BLUETOOTH
    SerialBT.begin(device_name); // Bluetooth device name
    //Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
    //Serial.printf("The device with name \"%s\" and MAC address %s is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str(), SerialBT.getMacString()); // Use this after the MAC method is implemented
      #ifdef USE_PIN
        SerialBT.setPin(pin);
        Serial.println("Using PIN");
      #endif

  //----------------pinMode
    // IR_Counter
    pinMode(irSensor1Pin, INPUT);
    pinMode(irSensor2Pin, INPUT);
    
    // Motor_PWM
    pinMode(PWM_FAN, OUTPUT); // To Digital Pin 2 of Motor Driver Shield
                              //* or EN pins for L298N H-Bridge Driver Module

    // TEMP_SENS
    pinMode(TEMP_SENS, INPUT);

    // Relay
    pinMode(AC_Relay_Pin, OUTPUT);
    pinMode(DC_Relay_Pin, OUTPUT);
}

void loop() {

  String speed = BT_LCD();    // Outputs a string
  //speed = TEMP();           // The current code is not supporting a simultaneous temp read to fan output;
  //speed = TEMP_FAN(tempC);  // Updates every 5 degree, change temp according to temp
  fanMotor(speed);            // if the string is a number, set the speed to that number.
  
  volatile int count = IR_Counter();
  LCD_Count(count);
  Relay(count);
  if (count == 0){            // Fan override: Turn OFF
    speed = "0";
  }
}
