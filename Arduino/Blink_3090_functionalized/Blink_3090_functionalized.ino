/*
  Blink_3090_functionalized

  Turns an LED on for one second, then off for one second, repeatedly.

  Pin 13 – Digital out: LED

  created 25 Feburary 2020
  by Steve Lammers

  Adapted from Blink_3090.ino
  
  This example code is in the public domain.

  Source code adapted from - http://www.arduino.cc/en/Tutorial/Blink
*/

// >>>>>>>>>>> Pin Definitions >>>>>>>>>>>>>>>>>>
#define LED_PIN 13
//int ledPin = 13;
// <<<<<<<<<<< Pin Definitions <<<<<<<<<<<<<<<<<<

// ************************** Setup **********************
// the setup function runs once when you press reset or power the board
void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_PIN, OUTPUT);

  Serial.print("LED_PIN: ");
  Serial.println(LED_PIN);
}

// the loop function runs over and over again forever
void loop() {
  blink_led(LED_PIN);
}

// >>>>>>>>>>> Sub Functions >>>>>>>>>>>>>>>>>>
//
// ****************** Blink_led ***************
//   Blinks LED on and off
//   
//  Arguments
//  int ledPin - Digital pin controlling LED
//
void blink_led(int ledPin){
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
//
// <<<<<<<<<<<< Sub Functions <<<<<<<<<<<<<<<<<<
