// Bluetooth Serial to LCD
  // This code provides communication between serial to bluetooth serial (SerialBT). 
  //    Serial displays on the PC, SerialBT displays on the LCD (if attached).
  //
  // This part of the code is under the data logger objective
// Tags: Data_Logger; SerialBT_LCD;

void displayStatus(Status status) {
  
  switch (status) {
    case READY_TO_RECEIVE:
      lcd.setCursor(0, 1);
      lcd.print("Ready to receive");
      break;
    case REPLAYING:
      lcd.setCursor(0, 1);
      lcd.print("Replaying...");
      break;
    case CONNECTED:
      lcd.setCursor(0, 1);
      lcd.print("Connected");
      break;
    case NOT_CONNECTED:
      lcd.setCursor(0, 1);
      lcd.print("Not Connected");
      break;
    case DISPLAYING:
      lcd.setCursor(0, 1);
      lcd.print("Displaying...");
      break;
    case RESET:
      lcd.setCursor(0, 1);
      lcd.print("               "); //Clear Row
      break;
  }
}

String BT_LCD() {
  unsigned long currentMillis = millis(); // Get the current time

  String receivedData = "";

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  // Check for new message
  while (SerialBT.available() > 0) {
    char incomingChar = SerialBT.read();
    Serial.print(incomingChar);

    // check for newline character or other control characters
    if (incomingChar != '\n' && incomingChar >= 32 && incomingChar <= 126) {
      receivedData += incomingChar;
    }
  }

  // Display the characters, allowing scrolling
  int dataLength = receivedData.length();

  if (dataLength > 0) {
    lcd.clear();
    if (dataLength <= 16) {
      lcd.setCursor(0, 0);
      lcd.print(receivedData);
      displayStatus(DISPLAYING);
      delay(50); // Just for effect hahaha
      previousMillis_IR = currentMillis;
    } else {
      // Plan to introduce variable scolling speed (Not Important)
      int scroll = 190; //ms


      for (int i = 0; i < dataLength + lcdColumns; ++i) {
        int index = i % dataLength; // Index at the end of 16 char
        lcd.clear();
        for (int j = 0; j < lcdColumns; ++j) {
          lcd.setCursor(j, 0);
          lcd.write(receivedData[(index + j) % dataLength]); // Indexed i + j will print the rest.
        }
        displayStatus(REPLAYING); // "Replaying" if over 16 characters
        delay(scroll); // Scrolling speed
        lcd.clear(); // Don't remove
      }
    }
    //lcd.clear(); // Remove displayStatus();
  } else {
    // Display a default message when there is no data
    // displayStatus(READY_TO_RECEIVE); // Counter is priority!!
    // delay(350);
  }
  if (currentMillis - previousMillis_IR >= 5000) {
    // Every 5 sec print, so don't put anything else. It will interfere the compiled code.
    lcd.setCursor(0,0);
    lcd.print(device_name);
  }

  return receivedData;
}