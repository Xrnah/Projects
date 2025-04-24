// Objective: Relay the temperature reading to TDS sensor as deviation compensation.

// Tags: Temperature (DHT11, LM35DZ (IC/Enclosed)); TDS_variable;

float TEMP() {
  
  temp_sensor.requestTemperatures(); // Send the command to get temperature readings
  float temperatureC = temp_sensor.getTempCByIndex(0); // Get the temperature in Celsius

    if (abs(temperatureC - prev_temp) >= 1.0) {
      Serial.printf("[Debug] Temp Celsius: %.2f°C\n", temperatureC);
      prev_temp = temperatureC;
    }
    
  return temperatureC;
}