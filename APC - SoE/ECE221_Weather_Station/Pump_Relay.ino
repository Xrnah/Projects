// Objective: To integrate the feedback device used to control the output
  // Utilizing the relay
  // ... potentially for a motor controlling a gate or a pump
//

void waterPump(){
  if (waterStatus == "High" || relaySwitch == 1){
    digitalWrite(RELAY_PIN, HIGH); // Turns the pump ON if water is high or the relay switch is activated
    relayIndicator = true; // Sets relay indicator to true, indicating the pump is running
  } else {
    digitalWrite(RELAY_PIN, LOW); // Turns the pump OFF if conditions are not met
    relayIndicator = false; // Sets relay indicator to false, indicating the pump is idle
  }
  
  if (relayIndicator == true){
    relayStatus = "Running"; // Sets relayStatus to "Running" when pump is ON
  } else {
    relayStatus = "Idle"; // Sets relayStatus to "Idle" when pump is OFF
  }

  // Update Blynk only if the indicator state changes
  if (relayIndicator != lastRelayIndicator) {
    Blynk.virtualWrite(V7, relayStatus); // Sends the current pump status to Blynk if there's a change
    lastRelayIndicator = relayIndicator; // Updates lastRelayIndicator to the current state
  } 
}