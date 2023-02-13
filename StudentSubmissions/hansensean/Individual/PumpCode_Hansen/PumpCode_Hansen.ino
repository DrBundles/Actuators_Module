// PERISTALTIC PUMP CODE - Sean Hansen
/*
 * This code is used to operate a small 3D printed peristaltic pump.
 * The pump is run off of a NEMA 17 stepper motor with as A4988 motor driver.
 * The code is able to accept user inputs for flow rate and tubing diameter.
 * It then calculates the delay for the stepper motor based on this.
 * 
 * TESTING:
 * Testing was necessary to ensure:
 *  That the UI was able to accept inputs for flow rate and tubing diameter.
 *  That increasing the flow rate increases the speed.
 *  That increasing the diameter decreases the speed.
 *  That if no inputs are selected, it defaults to generic values.
 *  
 * The results of the testing are shown in the attached video "DemonstrationVideo_Hansen.mp4".
 * TESTING RESULTS:
 *  The UI accepts inputs for both values and sets them correctly.
 *  Increasing the flow rate increases the speed.
 *  Increasing the diameter decreases the speed.
 *  When no inputs are selected, it defaults to flow rate of 1 cm^3/m and diameter of 0.2 cm.
 */

// >>>>>>>>>>> Pin Definitions >>>>>>>>>>>>>>>>>>
#define dirPin 2
#define stepPin 3
#define Button_Pin 5
#define LED_Pin 6
#define stepsPerRevolution 200 // not needed, just in case
#define pi 3.1415926535897932384626433832795 // needed for calcs below
// <<<<<<<<<<< Pin Definitions <<<<<<<<<<<<<<<<<<

// >>>>>>>>>>> Globals >>>>>>>>>>>>>>>>>>>>>>>>>>
bool ledState = false;            // flag for LED status
bool pbLatch = false;             // flag for push button latch
bool uiFlag = false;              // flag for asking for inputs
bool motorFlag = true;            // flag for stepper motor
double lastTime = 0;              // milliseconds, holds time value during main loop
double lastTime2 = 0;             // milliseconds, holds last time for motor
double pbDebounceDelay = 50;      // milliseconds for debounce delay
double flowRate;                  // flow rate (user defined)
double tubeDiam;                  // tube diameter (user defined)
double avel;                      // angular velocity for pump
unsigned long currentTime = 0;    // milliseconds 
unsigned long currentTime2 = 0;   // milliseconds(for motor)
unsigned long switchTime = 1000;  // milliseconds between blinking LED on and off
unsigned long switchTime2 = 200;    // milliseconds between motor steps
unsigned long pbLastDebounceTime = 0; // milliseconds for last debounce
// <<<<<<<<<<< Globals <<<<<<<<<<<<<<<<<<<<<<<<<<


// ******************* Setup *********************
// the setup function runs once when you press reset or power the board
void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // initialize digital pin LED_Pin as an output.
  pinMode(LED_Pin, OUTPUT);
  // initialize digital pin Button_Pin as input.
  pinMode(Button_Pin, INPUT);
  // initilizes output pins necessary for the stepper motor
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  // initialize timers for LED blinking
  lastTime = millis();
  currentTime = lastTime;
  // initialize timers for motor stepping
  lastTime2 = millis();
  currentTime2 = lastTime2;
} // end setup


// ******************* Main Loop ******************
void loop() {
// Main loop uses minimal code. Most code in subfunctions below.

// Calls a function to check user inputs
// Only runs once and then flags turn it off
// Asks for volumetric flowrate, tube length, and tube CS-area
if (uiFlag == false) { // only runs if flag is off
  user_inputs();
}

// Calls the pushbutton function to set the latch value
// A debounce function is embedded inside of it
pbLatch = check_pushbutton(pbLatch);

// Check if it is time to blink the LED
// and switch state if enough time has elapsed
// If the latch value is 0 the blinking is off
blink_timer(millis(),pbLatch);

// Calls the motor driver function
// Only runs if the LED is blinking and latch value is 1
motor_driver(millis(),pbLatch);
  
} // end loop

// >>>>>>>>>>> Sub Functions >>>>>>>>>>>>>>>>>>
//
// ****************** blink_led ***************
//  Blinks LED on and off
//   
//  Arguments
//  int ledPin - Digital pin controlling LED
//  bool ledOnOff - Controls whether LED is high or low
//
void blink_led(int ledPin, bool ledOnOff){
  digitalWrite(ledPin, ledOnOff);   // turn the LED on (HIGH is the voltage level)
}
//
// ****************** blink_timer ***************
//  Timing loop for LED blinking
//  
//  Arguments
//  unsigned long currentTime - current time since Arduino booted
//
void blink_timer(unsigned long currentTime, bool latchValue){
  if (((currentTime - lastTime) >= switchTime) && latchValue == true) {
    lastTime = currentTime; // resets the lastTime variable so it's current
    // Switch LED state if blink was triggered by timing loop
    ledState = !ledState; // flips ledState
    blink_led(LED_Pin, ledState); // runs blink function
    // This writes it low if the latch value is 0 to avoid a dim blink bug
  } else if (latchValue == false) {
    digitalWrite(LED_Pin, LOW); // turns light off when button off
  }
}
//
// ************** check_pushbutton **************
//  Checks push_button state
//
//  Arguments
//  bool latchValue - latch value for push button pin
//
bool check_pushbutton(bool latchValue) {
  // Reads if the button has been pushed
  if (digitalRead(Button_Pin)) {
    latchValue = pb_debounce(latchValue); // calls debounce function
    Serial.println("Button Pushed"); // for debugging
    while (digitalRead(Button_Pin)) {
    } // while the button is being pushed, don't do anything else
  }   
  // Turn off LED if pbLatch is false
  // otherwise it could stop blinking and still be on
  if (latchValue == false) {
    digitalWrite(LED_Pin, LOW);
  }
  return latchValue; // returns the variable as output
}
//
// **************** motor_driver ****************
//  Drives the motor
//  only runs when the latch from the button is set to 1
//
//  Arguments
//  bool latchValue - latch value for push button pin
//
void motor_driver(unsigned long currentTime2, bool latchValue) {
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);
  if (latchValue == true) { // only runs if button has been pressed
    // These lines result in 1 step, then it repeats:
    if ((currentTime2 - lastTime2) >= switchTime2) {
      lastTime2 = currentTime2; // updates timer variable
      digitalWrite(stepPin, motorFlag); // performs step
      motorFlag = !motorFlag; // flips the flag for the next step
    }
  }
}
//
// ***************** pb_debounce ****************
//  Debounces push button signal
//  code uses small delay but shouldn't be problem here
//  
//  Arguments
//  bool latchValue - latch value for push button pin
//
//  Outputs
//  bool - current latch value for push button after debounce
//
bool pb_debounce(bool latchValue) {
  pbLastDebounceTime = millis(); // gets current time
  delay(pbDebounceDelay); // pauses for debounce
  if (digitalRead(Button_Pin)) {
    latchValue = !latchValue; // reverses value for latch
    return latchValue; // returns the variable as output
  }
}
//
// **************** user_inputs *****************
//  Asks for user inputs for 3 variables
//  Sets values for:
//  Volumetric flow rate (mm^3 / s)
//  Tube length (mm)
//  Tube cross-sectional area (mm^2)
//  
//  No arguments or outputs, these variables are set globally
//
void user_inputs() {
  Serial.println("Please input flowrate and tubing geometry...");
  Serial.print("Volumetric Flowrate (cm^3/min): "); // asks for flowrate
  while(!Serial.available()) {} // waits until input received
  if(Serial.available() > 0){ // gets input once available
    flowRate = (Serial.parseFloat()); // sets variable in minutes
    Serial.print(flowRate); // prints value for confirmation
    Serial.println(" (cm^3/min)"); // prints units
    flowRate = flowRate/60; // converts flowRate to seconds for calc
    Serial.read(); // ensures the serial buffer is empty
  }
  Serial.print("Tubing Diameter (cm): "); // asks for tube diameter
  while(!Serial.available()) {} // waits until input received
  if(Serial.available() > 0){ // gets input once available
    tubeDiam = Serial.parseFloat(); // sets variable
    Serial.print(tubeDiam); // prints value for confirmation
    Serial.println(" (cm)"); // prints units
  }

  // SETS DEFAULTS:
  // generic step delay is ~426.2 ms for full step. 
  // Thus, rotates at 281.4 steps / min.
  if(flowRate == 0){
    Serial.println("Flow rate not specified, setting to default: 1 cm^3/min.");
    flowRate = 1.0/60; // sets flowRate to 1 cm^3/min (in seconds) if not defined
  }
  if(tubeDiam == 0){
    Serial.println("Tubing diameter not specified, setting to default: 0.2 cm.");
    tubeDiam = 0.2; // sets tubeDiam to 0.2 cm (approx. our tube diameter) if not defined
  }

  // These just print that you're all set once inputs have been read.
  Serial.println(""); // blank line to seperate this part from other text
  Serial.println("Flow rate and geometry values set...");
  Serial.println("Pump is ready to operate now. Please Proceed.");
  Serial.println(""); // blank line to seperate this part from other text

  // MATH:
  // v = (4*flowRate)/(pi*tubeDiam^2); (linear velocity)
  // w = v/r; radius of pump = 18 mm (angular velocity)
  avel = ((4*flowRate)/(pi*tubeDiam*tubeDiam))/1.8; // gets w (rad/s)
  // w is (rad/s) and the motor steps ((2*pi)/200) rads / step
  // Thus, to get seconds per step take (rad/step) and divide w (rad/s) to get (s/step).
  switchTime2 = (((2*pi)/200)/avel)*1000; // gets milliseconds per step
  switchTime2 = switchTime2/2; // Since the timer is 1/2 a step, divide total time by 2.
  
  uiFlag = true; // sets the flag to not run this function again
}
//
// <<<<<<<<<<<< Sub Functions <<<<<<<<<<<<<<<<<<
