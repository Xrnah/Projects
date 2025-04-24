// Objective: If the counter is over 1, turn the system on.
  // Optocoupled AC is connected to a AC_Lightbulb
    // it will switch on once with a delay of 4.5s
  // A delay is introduced to reduce a surge or transient current to occur on the A/C unit
    // *if the unit if not modernly automated.
// Tags: Optocoupled AC Line; Relay_Control; 

void Relay(int count){

  unsigned long currentMillis = millis(); // for switching delay

  if (count>=1){ // Switch ON
    if (currentMillis - previousMillis_AC >= delay_AC) {
    // Invert output on optocoupled relay; default is HIGH for Diorama DC LEDs (Just Relay);
    digitalWrite(AC_Relay_Pin, LOW); 
    digitalWrite(DC_Relay_Pin, HIGH);
    previousMillis_AC = currentMillis;
    }
  } else { // Switch OFF
    if (currentMillis - previousMillis_AC >= delay_AC) {
    digitalWrite(AC_Relay_Pin, HIGH);
    digitalWrite(DC_Relay_Pin, LOW);
    previousMillis_AC = currentMillis;
    }
  }
  
}
