/*
  Blink_3090_nodelay

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
// <<<<<<<<<<< Pin Definitions <<<<<<<<<<<<<<<<<<


// >>>>>>>>>>> Globals >>>>>>>>>>>>>>>>>>>>>>>>>>
bool ledState = false;
double lastTime = 0;              // milliseconds, holds time value during main loop
unsigned long currentTime = 0;    // milliseconds 
unsigned long switchTime = 1000;  // milliseconds between blinking LED on and off
// <<<<<<<<<<< Globals <<<<<<<<<<<<<<<<<<<<<<<<<<


// ******************* Setup *********************
// the setup function runs once when you press reset or power the board
void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_PIN, OUTPUT);
  // initialize timers for LED blinking
  lastTime = millis();
  currentTime = lastTime;
} // end setup


// ******************* Main Loop ******************
void loop() {

  // Check if it is time to blink the LED
  // and switch state if enough time has elapsed
  blink_timer(millis());
  
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
void blink_timer(unsigned long currentTime){

  if ((currentTime - lastTime) >= switchTime) {
    lastTime = currentTime;
    // Switch LED state if bBlink was triggered by timing loop
    ledState = !ledState;
    blink_led(LED_PIN, ledState);
  }

}
//
//
// <<<<<<<<<<<< Sub Functions <<<<<<<<<<<<<<<<<<
