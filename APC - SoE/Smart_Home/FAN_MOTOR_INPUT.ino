// Objective: Makes the MCU output a PWM, Analog (DAC), or Cosine Waveform.
  // This serves as the input to the Motor Controller 
  // Motor Controller: L293D (UNO shield) receives Analog (DAC) on pins A0-A5.
                    //  *additionally receives a PWM at digital pin 2
                    // L296N (Current Regulator Circuit) receives PWM at ENABLE pins 1 and 2.
                    //  *limited to be supplied by voltage above 5V

// Tags: Motor_Controller_Input; PWM; Analog (DAC); Cosine Wave;

//*Don't forget to program the motor driver shield (BT_MOTOR_SHIELD_OUTPUT.ino)

void fanMotor(String receivedData) {

  if (receivedData == "0") {
    FAN_SPEED = 0;
  } else if (receivedData == "1") {
    FAN_SPEED = 1;
  } else if (receivedData == "2") {
    FAN_SPEED = 2;
  } else if (receivedData == "3") {
    FAN_SPEED = 3;
  } else if (receivedData == "4"){
    FAN_SPEED = 4;
  }

  switch (FAN_SPEED) {
    case 1:
      analogWrite(PWM_FAN, 63);
      dacWrite(25, 63);
      break;
    case 2:
      analogWrite(PWM_FAN, 126);
      dacWrite(25, 126);
      break;
    case 3:
      analogWrite(PWM_FAN, 255);
      dacWrite(25, 255);
      break;
    case 4:                                 // Just an additional case (for testing) = case 3 is actual maximum
      analogWrite(PWM_FAN, 1023);           // Conclusion: Any number over 255 "saturates" the output
      dac1.outputCW(1000, DAC_CW_SCALE_1);  // Display for a cosine waveform at 1kHz on pin 25
      break;
    default:
      analogWrite(PWM_FAN, 0);
      dacWrite(25, 0);
      break;
  }
}