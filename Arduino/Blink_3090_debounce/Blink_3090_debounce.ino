/*
  Blink_3090_debounce

  Turns an LED on for one second, then off for one second, repeatedly.

  Pin 13 – Digital out: LED

  created 25 Feburary 2020
  by Steve Lammers

  This example code is in the public domain.

  Source code adapted from - http://www.arduino.cc/en/Tutorial/Blink
*/

// >>>>>>>>>>> Pin Definitions >>>>>>>>>>>>>>>>>>
#define LED_PIN 13
//int ledPin = 13;
#define PB_PIN 12
// <<<<<<<<<<< Pin Definitions <<<<<<<<<<<<<<<<<<


// >>>>>>>>>>> Globals >>>>>>>>>>>>>>>>>>>>>>>>>>
bool ledState = false;
double lastTime = 0;                  // milliseconds, holds time value during main loop
unsigned long currentTime = 0;        // milliseconds 
unsigned long switchTime = 1000;      // milliseconds between blinking LED on and off 
bool pbLatch = false;                 // Boolean latch for controlling LED blink
unsigned long pbLastDebounceTime = 0; // milliseconds time of last pb press
unsigned long pbDebounceDelay = 50;   // milliseconds delay for pusbbutton debounce
// <<<<<<<<<<< Globals <<<<<<<<<<<<<<<<<<<<<<<<<<


// ******************* Setup *********************
// the setup function runs once when you press reset or power the board
void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // initialize digital pins 
  pinMode(LED_PIN, OUTPUT);
  pinMode(PB_PIN, INPUT);
  // initialize timers for LED blinking
  lastTime = millis();
  currentTime = lastTime;
} // end setup


// ******************* Main Loop ******************
void loop() {

  // Check Pushbutton state
  //  and toggle pbLatch
  pbLatch = check_pushbutton(pbLatch);

  // Check if it is time to blink the LED
  // and switch state if enough time has elapsed
  blink_timer(millis(), pbLatch);
  
} // end loop


// >>>>>>>>>>> Sub Functions >>>>>>>>>>>>>>>>>>
//
//
// ****************** blink_led ***************
//   Blinks LED on and off
//   
//  Arguments
//  int ledPin - Digital pin controlling LED
//
void blink_led(int ledPin, bool ledOnOff){
  digitalWrite(ledPin, ledOnOff);   // turn the LED on (HIGH is the voltage level)
}
//
//
//
// ****************** blink_timer ***************
// Timing loop for LED blinking
//
void blink_timer(unsigned long currentTime, bool pbLatch){

  if ((currentTime - lastTime) >= switchTime) {
    lastTime = currentTime;
    // Switch LED state if bBlink was triggered by timing loop
    if (pbLatch) {
      ledState = !ledState;
      blink_led(LED_PIN, ledState);
    }
  }
}
//
//
// ****************** check_pushbutton ***************
// Check Pushbutton state and toggle pbLatch
//
bool check_pushbutton(bool latchValue) {
  // Poll state of the pushbutton, debounce if signal detected
  if (digitalRead(PB_PIN)){
    latchValue = pb_debounce(latchValue);
    while(digitalRead(PB_PIN)){
      
    }
  }

  // Turn off LED if pbLatch is false
  // otherwise it could stop blinking and still be on
  if (latchValue == false){
    digitalWrite(LED_PIN, false);
  }

  Serial.println(latchValue); // For debugging
  return latchValue;
}
//
//
// ****************** pb_debounce ***************
// Debounce pushbutton signal
// This code uses a small delay since it is only
//   run intermittently and the main loop is holding
//   for signal most of the time this delay should not
//   prove a problem here.
//
bool pb_debounce(bool latchValue){
  // Reset time for last time this function was called
  pbLastDebounceTime = millis(); 
  // After a short delay, check if the PB is still pressed
  // if so, switch latch value.
  delay(pbDebounceDelay);
  if(digitalRead(PB_PIN)){
    latchValue = !latchValue;
  }
  return latchValue;
}
