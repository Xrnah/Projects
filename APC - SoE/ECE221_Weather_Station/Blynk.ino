// Objective: To make an information and control deck on Blynk
  // Display Temperature and Relative Humidity (V1)
  // Display Rain & Flood
  // Display Air Pollution
  // Control for water pump
  // Control for water control

// Tags: Blynk; Internet-of-Things; Weather Station; Console;

/* Blynk Datastream Allocation: */
  // V0 - WaterLevelStatus - String
  // V1 - Blynk Terminal - Serial
  // V2 - Temperature - float
  // V3 - Humidity - float
  // V4 - Rain - String
  // V5 - Flood - String
  // V6 - Air Pollution - String
  // V7 - Water Pump Status - int
  // V8 - Water Pump Switch - asInt()
  // V9 - Terminal Filter Slider - asInt()
/* End of Allocation List */

WidgetTerminal terminal(V1);

BLYNK_CONNECTED(){
  Blynk.syncVirtual(V0, V1, V2, V3, V4, V5, V6, V7, V8, V9); // Sync virtual pins with the Blynk app (up to 10 pins in free plan)
  Serial.println("|. . . Weather Station: Online . . .|");  // Prints that the weather station is online
  // Serial.println("Reminder: Please wait for at least 2 seconds before issuing another command.");

  String currentTime = String(hour()) + ":" + 
                       String(minute()) + ":" + 
                       String(second());

  terminal.println("Connected at: " + currentTime); // Print the current time when connected to Blynk

}

void disconnectedBlynk(){
  if (connectedWiFi == true){ // Check if WiFi is connected
    if (!Blynk.connected()) {
    Serial.println("Disconnected from Blynk!");  // Notify if disconnected from Blynk
    Serial.println("Checking internet connection..."); // Notify action of checking internet connection
    }
  }
}

void reconnectWiFi(){
  if (WiFi.status() != WL_CONNECTED) {
    connectedWiFi = false;  // WiFi is disconnected
    unsigned long now = millis();
    if (now - lastReconnectAttempt >= 5000) { // Try to reconnect every 5 seconds
      lastReconnectAttempt = now;
      Serial.println("Attempting to reconnect to WiFi..."); // Notify user of WiFi reconnection attempt
      WiFi.reconnect(); // Attempt to reconnect to WiFi
    }
  }
  if (WiFi.status() == WL_CONNECTED){
    connectedWiFi = true; // If WiFi is connected, set the flag to true
  }
}

void blynkRefreshVariables(){
  double tempBlynk = double(trunc(temperature)); // Truncate temperature to an integer value
  double humidityBlynk = double(trunc(humidity)); // Truncate humidity to an integer value
  int waterLevel = waterLevelAverage(&waterStatus); // Get average water level from water status data
  int rainSensor = digitalRead(RAIN_HL_PIN); // Read the rain sensor's status

  DEBUG_BLYNK_PRINTf("[Blynk] Temp: %f \n", tempBlynk);       // Print temperature to Serial for debugging
  DEBUG_BLYNK_PRINTf("[Blynk] RH: %f %% \n", humidityBlynk);  // Print humidity to Serial for debugging
  if (tempBlynk >= VERY_HIGH_TEMP && humidityBlynk >= RH_THRESHOLD) {
    Blynk.logEvent("Heat_Index45"); // Trigger urgent notification event if temperature and humidity exceed high threshold
  } else if (tempBlynk >= HIGH_TEMP && humidityBlynk >= RH_THRESHOLD) {
    Blynk.logEvent("Heat_Index40"); // Trigger notification event for uncomfortable heat index level
  }

  DEBUG_BLYNK_PRINTf("[Blynk] Water Level: %f \n", waterLevel); // Print water level to Serial for debugging
  if (waterLevel >= FLOOD_HIGH_THRESHOLD){
    Blynk.logEvent("High_Water"); // Trigger notification event if water level exceeds flood threshold
  }

  DEBUG_BLYNK_PRINTf("[Blynk] Rain (4095-0): %d \n", rainSensor);  // Print rain sensor data
  if (rainSensor == LIGHT_RAIN_THRESHOLD){
    // Do Nothing
  } else if (rainSensor <= MODERATE_RAIN_THRESHOLD) {
    Blynk.logEvent("Rain_Moderate");  // Trigger notification for moderate rain event
  } else if (rainSensor <= HEAVY_RAIN_THRESHOLD){
    Blynk.logEvent("Rain_Heavy"); // Trigger urgent notification for heavy rain event
  } 

  if (!disconnectedDHT == true){ // Check if DHT sensor is connected
    // This is to avoid the graph from zooming out the actual data
    Blynk.virtualWrite(V2, tempBlynk); // Send temperature data to virtual pin V2
    Blynk.virtualWrite(V3, humidityBlynk); // Send humidity data to virtual pin V3
  }

  Blynk.virtualWrite(V4, rainStatus); // Send rain status to virtual pin V4
  // Blynk.virtualWrite(V4, rainBlynk); // Alternative variable for rainStatus
  Blynk.virtualWrite(V0, waterStatus); // Send water status to virtual pin V0
  Blynk.virtualWrite(V5, waterLevel); // Send water level data to virtual pin V5
  // Blynk.virtualWrite(V5, floodBlynk); // Old variable used in testing
  Blynk.virtualWrite(V6, airQuality); // Send air quality data to virtual pin V6

  /* Terminal Logic */ // This should output all raw values
  if (terminalSwitch == 1){
    switch (terminalSlider){  // This enables the terminal to selectively filter what to print
      case 1: // Print temperature 
        terminal.print("Temperature (°C): ");
        terminal.println(temperature);
        break;
      case 2: // Print temperature, humidity 
        terminal.print("Temperature (°C): ");
        terminal.println(temperature);

        terminal.print("Humidity (%): ");
        terminal.println(humidity);
        break;
      case 3: // Print temperature, humidity, water level
        terminal.print("Temperature (°C): ");
        terminal.println(temperature);

        terminal.print("Humidity (%): ");
        terminal.println(humidity);

        terminal.print("Water Level (0-2600):");
        terminal.println(waterLevel);
        break;
      case 4: // Print temperature, humidity, water level, rain level
        terminal.print("Temperature (°C): ");
        terminal.println(temperature);

        terminal.print("Humidity (%): ");
        terminal.println(humidity);

        terminal.print("Water Level (0-2600):");
        waterLevel = waterLevelAverage(&waterStatus);
        terminal.println(waterLevel);

        terminal.print("Rain (4095-0): ");
        terminal.println(rawRainSensor);

        break;

      case 5: // Print all + Air Pollution
        terminal.print("Temperature (°C): ");
        terminal.println(temperature);

        terminal.print("Humidity (%): ");
        terminal.println(humidity);

        terminal.print("Water Level (0-2600):");
        waterLevel = waterLevelAverage(&waterStatus);
        terminal.println(waterLevel);

        terminal.print("Rain (4095-0): ");
        terminal.println(rawRainSensor);

        terminal.print("Air Quality (0-2000+): ");
        terminal.println(rawAirPollution);

        break;

      case 10: // Print pinout info
        terminal.print(""); // Placeholder for pinout info (can be expanded)

        break;
      default:
        break;
    }
  }

}

BLYNK_WRITE(V1) { // Terminal input handler on V1
  String command = param.asStr();

  if (command == "on") {
    calibrationActive = true;   // Start MQ135 calibration
    terminal.println("MQ135 Calibration Initiated");
  } else if (command == "off") {
    calibrationActive = false;  // Stop MQ135 calibration
    terminal.println("MQ135 Calibration Stopped");
  } else {
    terminal.println("Invalid command. Use 'on' or 'off'.");  // Handle invalid input
  }
  terminal.flush();  // Sends the response to the terminal

}

BLYNK_WRITE(V8) { // Water Pump Switch

  int button = param.asInt(); // Reads the state of the button sent from Blynk (1 for ON, 0 for OFF)
    if (button == 1) {  // If the button is pressed (ON state)
    DEBUG_BLYNK_PRINTln("Water Pump: ON");  // Print debug message to Serial Monitor
    relaySwitch = 1;  // Set relaySwitch to 1 to turn the water pump ON (relaySwitch controls the relay state)
    } else {  // If the button is not pressed (OFF state)
    DEBUG_BLYNK_PRINTln("Water Pump: OFF");  // Print debug message to Serial Monitor
    relaySwitch = 0;  // Set relaySwitch to 0 to turn the water pump OFF
    }

    // A blynk call is executed separately on void waterPump()

}

BLYNK_WRITE(V9) { // Slider for Terminal Filter w/switch
  int slider = param.asInt(); // Read the value from the slider (an integer value)

  if (slider >= 1) {  // If the slider value is 1 or greater
    if (slider >= 1 && !terminalUpdatesOnPrinted) {  // Check if slider is set to 1 and the update hasn't been printed yet
        terminal.println("Terminal Updates: ON");  // Print the message that terminal updates are ON
        terminalUpdatesOnPrinted = true;  // Set the flag to indicate that the update message has been printed
    }
    terminalSwitch = 1;  // Enable terminal updates by setting terminalSwitch to 1
  } else {  // If the slider value is 0
    terminal.println("Terminal Updates: OFF");  // Print the message that terminal updates are OFF
    terminalSwitch = 0;  // Disable terminal updates by setting terminalSwitch to 0
    terminalUpdatesOnPrinted = false;  // Reset the flag so the message will be printed the next time slider is set to 1
  }

  terminalSlider = slider;  // Store the slider value to the terminalSlider variable for further use (e.g., for condition checking)

}