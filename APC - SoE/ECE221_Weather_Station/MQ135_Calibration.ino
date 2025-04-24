/*
  This part is used for calibration of MQ135 calibration being exposed to controlled air for more than 24 hours.
*/
void calibrate_Rzero_MQ135(){
  // Define variables for calculations
  float sensorVoltage = 0.0;    // Voltage read from the sensor
  float sensorResistance = 0.0; // Resistance of the sensor in fresh air
  float sensorValue = 0.0;      // Cumulative sensor reading
  float calibrationR0;          // Calibration factor for R0
  
  // Read analog value multiple times for an average
  for (int x = 0; x < 500; x++) {
    sensorValue += analogRead(AIR_MQ_PIN);
  }
  sensorValue /= 500.0; // Calculate average ADC value

  // Convert ADC value to sensor voltage
  const float supplyVoltage = 3.3;          // ESP32 ADC reference voltage
  const float maxADC = 4095.0;              // Maximum ADC value for 12-bit resolution
  sensorVoltage = sensorValue * (supplyVoltage / maxADC); 

  // Calculate sensor resistance in air
  const float loadResistance = 10.0;        // Load resistor value in kOhms
  sensorResistance = ((supplyVoltage * loadResistance) / sensorVoltage) - loadResistance;

  // Calculate R0 for calibration
  const float cleanAirFactor = 4.4;         // Typical clean air factor for MQ135
  calibrationR0 = sensorResistance / cleanAirFactor;

  // Print results to Serial Monitor
  Serial.print("Raw ADC = "); 
  Serial.println(sensorValue);               // Display averaged ADC output

  Serial.print("Sensor Voltage = ");
  Serial.println(sensorVoltage);             // Display calculated voltage

  Serial.print("Sensor Resistance (RS) = ");
  Serial.println(sensorResistance);          // Display sensor resistance in fresh air

  Serial.print("R0 (calibration factor) = ");
  Serial.println(calibrationR0);             // Display calculated R0
  
  // Print results to Blynk Terminal
  terminal.print("Raw ADC = "); 
  terminal.println(sensorValue);               // Display averaged ADC output

  terminal.print("Sensor Voltage = ");
  terminal.println(sensorVoltage);             // Display calculated voltage

  terminal.print("Sensor Resistance (RS) = ");
  terminal.println(sensorResistance);          // Display sensor resistance in fresh air

  terminal.print("R0 (calibration factor) = ");
  terminal.println(calibrationR0);             // Display calculated R0
  
  // delay(1000); // Delay 1 second before next loop iteration
}

void calibrate_R0_MQ135_Wrapper(){
    // Only set up the timer if calibrationActive is true
    if (calibrationActive && timerAirQualityID == -1) { // If timer is not already set
      calibrate_Rzero_MQ135();
    } else if (!calibrationActive && timerAirQualityID != -1) {
      timerAirQualityID = -1;  // Reset timer ID
    }
  
}