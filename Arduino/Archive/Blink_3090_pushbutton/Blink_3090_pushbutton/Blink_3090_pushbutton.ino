/*
  Blink_3090_timed

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

  // pbLatch is a local variable, does not have global scope
  // so it needs to be passed to and from functions.
  // Boolean latch for controlling LED blink
  bool pbLatch = false; 
  
  // Poll state of the pushbutton, debounce if signal detected
  if (digitalRead(PB_PIN)){
    pbLatch = pb_debounce(pbLatch);
  }
 
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
//
// ****************** pb_debounce ***************
// Debounce pushbutton signal
// This code uses a small delay since it is only
//   run intermittently and the main loop is holding
//   for signal most of the time this delay should not
//   prove a problem here.
//
bool pb_debounce(bool latchValue){
  pbLastDebounceTime = millis();
  delay(pbDebounceDelay);
  if(digitalRead(PB_PIN)){
    latchValue = !latchValue;
  }
  return latchValue;
}
//
//
// <<<<<<<<<<<< Sub Functions <<<<<<<<<<<<<<<<<<