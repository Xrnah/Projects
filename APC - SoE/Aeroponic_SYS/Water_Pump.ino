// Objective: Set a predetermined motor routine to supply water (nutrients) at an interval or interrupt
  // Update: 24/7 Pump = 12V 0.7A = 8.4W or approx. 9W consumption
  // Current sensor to be implemented: target of 700-800mA
    // if not: less than 700 = leak; more than 800 = clogged;
// Tags: Relay; 12V Motor;

void Water_Pump(float pHValue, float tdsValue) {
  
  if (!(pHValue <= max_pH_value && pHValue >= min_pH_value) && !(tdsValue <= max_tds_value && tdsValue >= min_tds_value)){
    
    digitalWrite(Pump_Relay, LOW);
    Serial.printf("[Debug] [OFF] pH: %.2f   TDS: %.2f \n", pHValue, tdsValue);
    
    if (!(pHValue <= max_pH_value && pHValue >= min_pH_value)){             // If pH or TDS value is out of range, trigger a tone to specify
      buzzer.tone(NOTE_E1, 250);
    } else if (!(tdsValue >= min_tds_value && tdsValue <= min_tds_value)){
      buzzer.tone(NOTE_D7, 250);
    }

  }else{

    digitalWrite(Pump_Relay, HIGH);
    Serial.printf("[Debug] [ON] pH: %.2f   TDS: %.2f \n", pHValue, tdsValue); // Used to check whether static values carries.
    buzzer.noTone();

  }

}

float Pump_Current(){
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();

  unsigned int x = 0;
  float SenValue = 0.0, Samples = 0.0, AvgVal = 0.0, Ampere = 0.0, milliAmp = 0.0;

  if(millis() - samplingTime > samplingInterval_motor){
      for (int x = 0; x < 150; x++){    // Get 150 samples
        SenValue = analogRead(34);      // Read current sensor values   
        Samples = Samples + SenValue;   // Add samples together
        }
      AvgVal = Samples/150.0;           // Taking Average of Samples    
      Ampere = (1.9755 - (AvgVal * (3.3 / 4095.0)) )/0.100;
      milliAmp = Ampere * 1000;
      samplingTime = millis();
  }
  
  if(millis() - printTime > printInterval_motor){   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
    Serial.printf("%d mA \n", milliAmp);  // Print the read current on Serial monitor  
    printTime = millis();
  }
  

  return milliAmp;
}