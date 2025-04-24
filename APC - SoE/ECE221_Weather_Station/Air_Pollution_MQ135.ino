// Objective: Measure Air Pollution using MQ-135 Sensor
  // To calibrate sensor according to CO2 concentration
  // Output warnings based on readings
  
// Tags: 

void readAirPollution() {

  // Read the analog value from the MQ-135 sensor connected to the defined pin (AIR_MQ_PIN)
  // This will give the raw sensor value representing the concentration of pollutants
  int sensorValue = analogRead(AIR_MQ_PIN);
  
  // The following lines of code are commented out but indicate potential methods
  // for calibrating the sensor according to temperature and humidity:
  // float cFactor = 0;
  // if (!isnan(temperature) && !isnan(humidity)) cFactor = getCorrectionFactor(temperature, humidity);
  // // Serial.print("Correction Factor: "); Serial.println(cFactor);
  // MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
  // int sensorValue = MQ135.readSensor(false, cFactor); // Use model coefficients and correction factor for more precise reading
  // // MQ135.serialDebug(); // Prints debug info to serial port, useful for calibration
  
  // Print the sensor value and voltage
  DEBUG_AIR_PRINTf("Analog Value: %d", sensorValue);
  // DEBUG_AIR_PRINTf("\t Voltage: %d V", voltage);

  // Classify air quality based on the raw sensor value (sensorValue)
  // The sensor value is compared to predefined thresholds for air quality categories
  if (sensorValue <= GOOD_AIR) {
    // If the sensor value is within the range for "Good" air quality
    DEBUG_AIR_PRINTln("Air Quality: Good (0-50 AQI)");
    airQuality = "Good (0-50 AQI)";
  } else if (sensorValue <= MODERATE_AIR) {
    // If the sensor value falls within the range for "Moderate" air quality
    DEBUG_AIR_PRINTln("Air Quality: Moderate (51-100 AQI)");
    airQuality = "Moderate (51-100 AQI)";
  } else if (sensorValue <= UNHEALTHY_SENSITIVE) {
    // If the sensor value falls within the "Unhealthy for Sensitive Groups" range
    DEBUG_AIR_PRINTln("Air Quality: Unhealthy for Sensitive Groups (101-150 AQI)");
    airQuality = "Unhealthy for Sensitive Groups (101-150 AQI)";
  } else if (sensorValue <= UNHEALTHY_AIR) {
    // If the sensor value indicates "Unhealthy" air quality
    DEBUG_AIR_PRINTln("Air Quality: Unhealthy (151-200 AQI)");
    airQuality = "Unhealthy (151-200 AQI)";
  } else if (sensorValue <= VERY_UNHEALTHY_AIR) {
    // If the sensor value falls into the "Very Unhealthy" range
    DEBUG_AIR_PRINTln("Air Quality: Very Unhealthy (201-300 AQI)");
    airQuality = "Very Unhealthy (201-300 AQI)";
  } else if (sensorValue <= HAZARDOUS_AIR) {
    // If the sensor value is within the "Hazardous" air quality range
    DEBUG_AIR_PRINTln("Air Quality: Hazardous (301-500 AQI)");
    airQuality = "Hazardous (301-500 AQI)";
  } else {
    // If the sensor value is above the "Hazardous" threshold, indicating "Extremely Hazardous" air quality
    DEBUG_AIR_PRINTln("Air Quality: Extremely Hazardous (500+ AQI)");
    airQuality = "Extremely Hazardous (500+ AQI)";
  }

  // Store the raw sensor value in a variable for potential further processing
  rawAirPollution = sensorValue;

}

// The following functions for calculating correction factors and converting resistance to PPM are commented out.
// These would be useful for precise calibration based on temperature, humidity, and sensor resistance values.
// These need MQUnifiedsensor library

// float getCorrectionFactor(float t, float h) {
//   return CORA * t * t - CORB * t + CORC - (h-33.)*CORD;
// }
// float getCorrectedResistance(long resvalue, float t, float h) {
//   return resvalue/getCorrectionFactor(t, h);
// }
// float getCorrectedPPM(long resvalue,float t, float h, long ro) {
//   return PARA * pow((getCorrectedResistance(resvalue, t, h)/ro), -PARB);
// }
