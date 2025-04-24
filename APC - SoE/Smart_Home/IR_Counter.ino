// Objective: Visitor/People Counter using IR sensor
  //
  //*[Debug] tags should be commented out once deployed
    // or maintained on demo as there is no output on Serial for display.
// Tags: IR_Sensor; LCD_Counter;


volatile int IR_Counter() {

  unsigned long currentMillis = millis(); // Get the current time

  irSensor1State = digitalRead(irSensor1Pin);
  irSensor2State = digitalRead(irSensor2Pin);

  // Check if both sensors are triggered == Don't COUNT
  if (irSensor1State == LOW && irSensor2State == LOW) {
    // Reset all flags and exit to prevent continuous counting
    sensor1Triggered = false;
    sensor2Triggered = false;
    sensor1TriggeredAfterSensor2 = false;
    sensor2TriggeredAfterSensor1 = false;
    return count;
  }

//Sensor Timeout
  if (irSensor1State == HIGH && irSensor2State == HIGH && (sensor1Triggered == true || sensor2Triggered == true)){
    Serial.printf("[Debug] Counting: \%d\n", (currentMillis - previousMillis_IR));

      if (currentMillis - previousMillis_IR >= IR_reset_time){
      previousMillis_IR = currentMillis;
      sensor1Triggered = false;
      sensor2Triggered = false;
      sensor1TriggeredAfterSensor2 = false;
      sensor2TriggeredAfterSensor1 = false;
      Serial.printf("[Debug] Sensor Timed Out \n");
      return count;
      }

}

//Triggered State [A]
  // If IR sensor 1 is triggered
  if (irSensor1State == LOW && !sensor2Triggered) {
    if (sensor1Triggered == false){
      Serial.print("[Debug] Sensor IN Triggered [1]\n");
    } else {
      Serial.print("[Debug] Sensor IN Triggered Again [1.A]\n");
      previousMillis_IR = currentMillis; //Reset Timeout
    }
    sensor1Triggered = true; // Set the flag to indicate sensor 1 is triggered
    sensor2TriggeredAfterSensor1 = false; // Reset the flag for IR sensor 2 triggered after sensor 1
    
  } 
  // If IR sensor 2 is triggered 
  if (irSensor2State == LOW && !sensor1Triggered) { 
    if (sensor2Triggered == false){
      Serial.print("[Debug] Sensor OUT Triggered [2]\n");
    } else {
      Serial.print("[Debug] Sensor OUT Triggered Again [2.A]\n");
      previousMillis_IR = currentMillis; //Reset Timeout
    }
    sensor2Triggered = true; 
    sensor1TriggeredAfterSensor2 = false;
    
}

//Triggered State [B] = before Timeout and after another sensor
  // If IR sensor 2 is triggered after IR sensor 1
  if (irSensor2State == LOW && sensor1Triggered && !sensor2TriggeredAfterSensor1) {
    sensor2TriggeredAfterSensor1 = true; // Set the flag to indicate IR sensor 2 is triggered after sensor 1
    delay(sensorHoldTime); // Delay to ensure the person is holding at sensor 2
  } 
  // If IR sensor 1 is triggered after IR sensor 2
  if (irSensor1State == LOW && sensor2Triggered && !sensor1TriggeredAfterSensor2) {
    sensor1TriggeredAfterSensor2 = true; 
    delay(sensorHoldTime);
}

//Triggered State [C] = change count
  // If IR sensor 2 is triggered again after holding
  if (irSensor2State == LOW && sensor1Triggered && sensor2TriggeredAfterSensor1) {
    count++;
    Serial.print("Person entered. Total count: ");
    Serial.println(count);

    sensor1Triggered = false; 
    sensor2TriggeredAfterSensor1 = false; 
    previousMillis_IR = currentMillis; // Record the time of the count
  }
  // If IR sensor 1 is triggered again after holding
  if (irSensor1State == LOW && sensor2Triggered && sensor1TriggeredAfterSensor2) {
    count--;
    if (count < 0) {
      count = 0; // count should not display negative values
    }
    Serial.print("Person left. Total count: ");
    Serial.println(count);

    sensor1Triggered = false; // Reset sensor 1 flag
    sensor2Triggered = false; // Reset sensor 2 flag
    sensor1TriggeredAfterSensor2 = false; // Reset flag for sensor 1 triggered after sensor 2
    previousMillis_IR = currentMillis; // Record the time of the count
}

  // Non-blocking delay: Wait for delayBetweenCounts milliseconds
  if (currentMillis - previousMillis_IR >= delayBetweenCounts) {
    // Do nothing; just proceed with the rest of the loop
  }
  return count;
}

void LCD_Count(volatile int count){
  
  int UpperLimit = 20;
  
  volatile static int previous_count = -1;

   // Check if count has changed - Bluetooth Terminal Limit
  if (previous_count != count) {
    SerialBT.printf("Count: \%d\n", count);
    previous_count = count;
    
    lcd.setCursor(0, 1);
    lcd.print("Count: ");

    // Handle place value and omit leading zeros
    if (count < 10) {
      lcd.print(" "); // Add a space before single-digit numbers
    }
    
    if (count > UpperLimit){
        lcd.setCursor(7, 1);
        lcd.print("MAX COUNT");
    } else {
      lcd.print(count);
      lcd.print("         "); //Erase MAX COUNT
    }
  }

}
