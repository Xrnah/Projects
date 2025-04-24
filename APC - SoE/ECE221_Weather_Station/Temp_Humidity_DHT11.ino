// Objective: Read temperature and humidity values from a DHT11 sensor.
  // Pass the values to display on OLED and Blynk
  // Assess comfort via heat index 

// Tags: DHT11; temperature; humidity; comfort;

void sensorDHT11(float* humidity, float* temperature) {
  float humidity_DHT = dht.readHumidity();           // Read humidity from DHT sensor
  float temperature_DHT = dht.readTemperature();     // Read temperature from DHT sensor (Celsius by default)
  static bool hasPrintedError = false;               // Tracks if an error message has already been printed

  if (isnan(humidity_DHT) || isnan(temperature_DHT)) {
    // Check if readings are valid; if either is Not a Number (NaN), print error
    if (!hasPrintedError) { 
        DEBUG_DHT_PRINTln("[Error] Failed to read from DHT sensor!"); // Print error message once
        hasPrintedError = true;     // Prevents repeated error messages
        disconnectedDHT = hasPrintedError; // Indicates DHT sensor is disconnected or has failed
    }
    return; // Exit the function if readings are invalid
  } else {
    // Reset the error flag if readings are valid again
    hasPrintedError = false;       // Enables error message on next failure
    disconnectedDHT = hasPrintedError; // Indicates successful reconnection
  }
  
  *humidity = humidity_DHT;            // Update humidity pointer with valid reading
  *temperature = temperature_DHT - 2.4; // Adjust temperature for known sensor deviation
}

void assessComfort(float* temperature, float* humidity) {
  if (*temperature > ROOM_TEMP && *humidity > RH_THRESHOLD) {
    DEBUG_DHT_PRINTln("[DHT] Uncomfortable: Hot and Humid"); // Hot and humid condition
  } else if (*temperature > ROOM_TEMP && *humidity <= RH_THRESHOLD) {
    DEBUG_DHT_PRINTln("[DHT] Warm but Tolerable");           // Warm but within tolerable humidity
  } else if (*temperature <= ROOM_TEMP && *humidity > RH_THRESHOLD) {
    DEBUG_DHT_PRINTln("[DHT] Cool but Humid");               // Cool but with high humidity
  } else {
    DEBUG_DHT_PRINTln("[DHT] Comfortable");                  // Comfortable condition
  }
}

void assessComfortWrapper() {
  assessComfort(&temperature, &humidity); // The wrapper function assessComfortWrapper allows calling 
                                            // ... assessComfort without passing pointers each time.
}
