int pwm_value = 0;
int percentage = 0;
void setup() {
  // Turn off the timer while we make changes
  TCCR1B = TCCR1B & ~ ((1 << CS12) | (1 << CS11) | (1 << CS10));
  
  // Ensure the Timer 1 output pins are configured for output
  pinMode( 9, OUTPUT );
  pinMode( 10, OUTPUT );
  
  // Set Compare Output Mode and part of the Waveform Generation Mode (mode 14)
  TCCR1A = 
      (1 << COM1A1) | (0 << COM1A0)  // Clear OC1A on Compare Match, set OC1A at BOTTOM (non-inverting mode)
      |
      (1 << COM1B1) | (1 << COM1B0)  // Set OC1B on Compare Match, clear OC1B at BOTTOM (inverting mode)
      |
      (1 << WGM11) | (0 << WGM10);  // Mode 14: Fast PWM, TOP = ICR1, Update of OCR1x at BOTTOM, TOV1 Flag Set on TOP

  // Set the other half of the Waveform Generation Mode (mode 14) and ensure a few things are disabled
  TCCR1B =
      (0 << ICNC1)  // Input Capture Noise Canceler disabled
      |
      (0 << ICES1)  // Input Capture Edge Select don't care
      |
      (1 << WGM13) | (1 << WGM12)  // Mode 14: Fast PWM, TOP = ICR1, Update of OCR1x at BOTTOM, TOV1 Flag Set on TOP
      |
      (0 << CS12) | (0 << CS11) | (0 << CS10);  // Clock continues to be disabled.  Not yet finished configuring.

  // Set the output frequency
  // fOCnxPWM = fclk_I/O / (N * (1 + TOP))
  // fOCnxPWM = 16000000 / (8 * (1 + 99))
  // fOCnxPWM = 20000 Hz
  ICR1 = 99;
  
  // Start with both outputs turned off
  OCR1A = 0;
  OCR1B = 99;
  
  // Start the clock
  TCCR1B = 
      TCCR1B 
      |
      (0 << CS12) | (1 << CS11) | (0 << CS10);  // clkI/O/8 (From prescaler)


  Serial.begin(115200);

}

void loop() {
//  for(int i=0,;i>255

  //delay(500);
  pwm_value = analogRead(A0);
  percentage = map(pwm_value,0,1023,25,60);
  Serial.print(percentage); 
  Serial.print('\n');
 // delay(100);
  analogWrite(9,percentage);

}
