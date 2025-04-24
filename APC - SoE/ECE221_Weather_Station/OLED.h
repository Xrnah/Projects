// Objective: Displays the measurements of every sensor and Wi-Fi connectivity status.

// Tags: OLED; Adafruit_SSD1306;

void OLED_Display(float* temperature, float* humidity){

  //-----Set Text Font
    // Set the text size to 1 (smallest size); affects all printed text until changed
    display.setTextSize(1);
    // Set text color to white; all text displayed will appear white against the OLED's black background
    display.setTextColor(WHITE);

  //-----Set Display Buffer (Content)

    display.setCursor(13,0);                              // Line 1 (Header)
    display.print("Weather Station");                     // Display header to label the OLED content
    
    // Set cursor for a blank line to create spacing between header and data
    display.setCursor(5,9);                               // Line 2 (NO CONTENT - SPACE)
    display.println("\n");                                // Print a newline to space out the display 

    display.setCursor(5,18);                              // Line 3 (Temperature)
    display.printf("Temp: \%.1f C", *temperature);        // Display temperature with 1 decimal point

    display.setCursor(5,27);                              // Line 4 (Humidity)
    display.printf("Humidity: %.1f %%", *humidity);       // Display humidity with 1 decimal point and a % sign

    display.setCursor(5,36);                              // Line 5 (Flood)
    display.printf("Water Level: %s", waterStatus);       // Show whether flooding is detected

    display.setCursor(5,45);                              // Line 6 (Rain)
    display.printf("Rain: %s", rainStatus);               // Show whether rain is detected

    display.setCursor(5,54);                              // Line 7 (Air Pollution)
    display.printf("Air: %d ppm", rawAirPollution);       // Display raw air pollution level in parts per million (ppm)

    display.setCursor(5,63);
    // display.print("8"); 
    
    // Optional line for future content (commented out for now)
    // display.setCursor(5,63);
    // display.print("8");    // Line 8 - [letter: half vertical cut]

    // Optional wake-up feature using a button to control OLED brightness
    // Checks if button pin is HIGH; dims display if not pressed, otherwise it stays bright
    // int button = digitalRead(BUTTON_PIN);
    // if (button == HIGH){
    //   display.dim(true);
    // } else {
    //   display.dim(false);
    // }

  // Display everything in the buffer on the OLED screen at once
    display.display();
    
  // Clear the buffer after displaying to remove previous content for the next update
    display.clearDisplay();
  }
