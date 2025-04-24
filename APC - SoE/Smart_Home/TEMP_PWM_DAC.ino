// Objective: Read the temperature and outputs a signal according to the ratio between FAN_SPEED and TEMP_Value

// Tags: Temperature (DHT11, LM35DZ (IC/Enclosed)); Temp-to-Fan Ratio;

String TEMP() {
  
  unsigned long currentMillis = millis();
  // after testing, interval should be based whether the temperature is changed by 5 degrees.

    // Get the voltage reading from the LM35
    int reading = analogRead(TEMP_SENS); //Analog read less than 100mV from testing
    //Serial.println(reading);

    // Convert that reading into voltage
    float voltage = reading * ((5+100)/ 1024.0);  // Voltage Resolution from AnalogRead = (Volt/res) //3.3 or 5V still the same output = ref:5V
                                                  //Analog read less than 100mV from testing [(Volt + 100deviation)/Res]
    //Serial.println(voltage);

    // Convert the voltage into the temperature in Celsius
    float Celsius = voltage + 10;   // Need +10 for temp deviation
                                    // *+2 real temp deviation (Body to Surface)
    
    if (abs(Celsius - prev_temp) >= 5){
      Serial.printf("[Debug] Temp Celsius: \%.2f\xC2\xB0 C\n", Celsius);
      // \%.2f (2 decimal float); \xC2\xB0 = ° (UTF-8 degree sign); 
      
      prev_temp = Celsius;

      //previously TEMP_FAN();
      String speed = ""; //0, 1, 2, 3

      if (Celsius > 35){
        speed = "3";
      } else if (Celsius > 32){
        speed = "2";
      } else if (Celsius > 27){   // People feel at least -5 degrees when fan is ON.
        speed = "1";              // ref: Body vs Surface calibration of industry standard IR thermometer
      } else {
        speed = "0";
      }
      //Serial.printf("[Debug] Speed set by temp to \%s\n", speed);
      return speed;
    }
}
