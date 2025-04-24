// Objective: Used to measure raindrops
  // Based on PAGASA rainfall advisory

void rainCheck(String* rainStatus) {
  int sensorStatus = analogRead(RAIN_HL_PIN); // Read the analog value from the rain sensor
  
  // Check and classify the status of the rain sensor
  if (sensorStatus >= MODERATE_RAIN_THRESHOLD && sensorStatus < LIGHT_RAIN_THRESHOLD) { 
    // If sensorStatus is between moderate and light thresholds, classify as Light Rain
    DEBUG_RAIN_PRINTln("Light Rain");
    *rainStatus = "Light Rain"; // Set rainStatus to "Light Rain"
  } else if (sensorStatus >= HEAVY_RAIN_THRESHOLD && sensorStatus < MODERATE_RAIN_THRESHOLD) {
    // If sensorStatus is between heavy and moderate thresholds, classify as Moderate Rain
    DEBUG_RAIN_PRINTln("Moderate Rain");
    *rainStatus = "Moderate Rain"; // Set rainStatus to "Moderate Rain"
  } else if (sensorStatus < HEAVY_RAIN_THRESHOLD) { 
    // If sensorStatus is below the heavy threshold, classify as Heavy Rain
    DEBUG_RAIN_PRINTln("Heavy Rain");
    *rainStatus = "Heavy Rain"; // Set rainStatus to "Heavy Rain"
  } else { 
    // If sensorStatus does not fall within any rain thresholds, classify as Dry
    DEBUG_RAIN_PRINTln("Dry");
    *rainStatus = "Dry"; // Set rainStatus to "Dry"
  }

  rawRainSensor = sensorStatus; // Store raw sensor reading for further analysis
}

void rainCheckWrapper(){
  rainCheck(&rainStatus); // Wrapper function to call rainCheck with rainStatus as a reference
}