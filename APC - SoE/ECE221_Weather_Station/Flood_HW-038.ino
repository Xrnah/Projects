// Objective: Read water level from HW-038
  // Output is sent to a global variable via a pointer
    // ...for ease of access across functions

// Tags: HW-038; Flood Level; Warning System;

int waterLevelAverage(String* waterStatus){
  // Subtract the oldest reading from the total to maintain an accurate moving average
  total -= readings[readIndex];

  // Read the current value from the flood sensor
  int instant = analogRead(FLOOD_HW_PIN); // Read the value once

  // Store the new reading in the readings array
  readings[readIndex] = instant;          // Store it in the readings array

  // Add the new reading to the total to update the sum of all readings
  total += readings[readIndex];           // Increment the total by the current reading

  // Move to the next index, wrapping around if necessary
  readIndex = (readIndex + 1) % NUM_READINGS; 
    // The modulo operation ensures the index loops back to 0 after reaching NUM_READINGS

  // Calculate the average value by dividing the total sum by the number of readings
  average = total / NUM_READINGS;   // The average of the most recent readings is calculated here

  // Debug output to print real-time and smoothed sensor values for diagnostic purposes
  DEBUG_FLOOD_PRINTf("[Water Level] Real Time value: %d \n", instant); // Print the raw value read from the sensor
  DEBUG_FLOOD_PRINTf("[Water Level] Smoothed Sensor value: %d \n", average); // Print the smoothed average value

  // Determine water level based on the average value
  // Compare the average value to defined thresholds to classify the water level
  if (average < FLOOD_EMPTY_THRESHOLD) {
    // If the average value is below the threshold for "Empty", set status to "Empty"
    DEBUG_FLOOD_PRINTln("Water Level: Empty");
    *waterStatus = "Empty";  // Dereference the pointer and set the status to "Empty"
  } else if (average <= FLOOD_LOW_THRESHOLD) {
    // If the average is between the "Empty" and "Low" thresholds, set status to "Low"
    DEBUG_FLOOD_PRINTln("Water Level: Low");
    *waterStatus = "Low";    // Dereference the pointer and set the status to "Low"
  } else if (average <= FLOOD_HIGH_THRESHOLD) {
    // If the average is between the "Low" and "High" thresholds, set status to "Medium"
    DEBUG_FLOOD_PRINTln("Water Level: Medium");
    *waterStatus = "Medium"; // Dereference the pointer and set the status to "Medium"
  } else {
    // If the average exceeds the "High" threshold, set status to "High"
    DEBUG_FLOOD_PRINTln("Water Level: High");
    *waterStatus = "High";   // Dereference the pointer and set the status to "High"
  }

  // Return the average sensor value for further processing
  return average;
}

void waterLevelAverageWrapper(){
  // Call waterLevelAverage and pass waterStatus as a pointer to update its value
  waterLevelAverage(&waterStatus);
}
