// Objective: Displays the measurements of every sensor and Wi-Fi connectivity status.

// Tags: OLED; Adafruit_SSD1306;

void OLED_Display(float temperature, float pH_value, float TDS_value, int button = 0){

    // Set Text Font
    display.setTextSize(1);
    display.setTextColor(WHITE);

    // Set Display Buffer (Content)
    display.setCursor(12,0); 
    display.print("Aeroponic System"); // Header Line

    display.setCursor(5,9);
    display.println("\n"); // Line 2 (NO CONTENT - SPACE)

    display.setCursor(5,18);
    display.printf("pH: %.2f", pH_value); // Line 3
    display.setCursor(5,27);
    display.printf("TDS: %.2f", TDS_value); // Line 4
    display.setCursor(5,36);
    display.printf("Temp: %.2f", temperature); // Line 5

    // Check pH value and TDS value
    display.setCursor(5, 45);
    bool error = false;
    if (pH_value < 4.8 || pH_value > 6.4) {
        display.print("Check Water (pH)"); // Line 6
        error = true;
    }
    if (TDS_value < 450 || TDS_value > 780) {
        if (error) {
            display.setCursor(5, 54); // Move to the next line if there's already an error
        }
        display.print("Check Water (TDS)"); // Line 7 or 6 if no previous error
        error = true;
    }
    if (!error) {
        display.print("Status: OK"); // Line 6
    }

    display.setCursor(5,63);
    // display.print("8"); // Line 8 - [letter: half vertical cut]
    
    // button - [Don't forget current limiting resistor]
    // button = digitalRead(BUTTON_PIN);
    if (button == HIGH){
      display.dim(true);
    } else {
      display.dim(false);
    }

    // Display [Buffer]
    display.display();
    
    // Clear Buffer (Resets pixels to 0)
    display.clearDisplay();
  }
