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
#define STEP_PIN 8
#define DIR_PIN 9 
// <<<<<<<<<<< Pin Definitions <<<<<<<<<<<<<<<<<<


// >>>>>>>>>>> Globals >>>>>>>>>>>>>>>>>>>>>>>>>>
bool ledState = false;
double lastTime = 0;                  // milliseconds, holds time value during main loop
unsigned long currentTime = 0;        // milliseconds 
unsigned long switchTime = 1000;      // milliseconds between blinking LED on and off 
bool pbLatch = false;                 // Boolean latch for controlling LED blink
unsigned long pbLastDebounceTime = 0; // milliseconds time of last pb press
unsigned long pbDebounceDelay = 50;   // milliseconds delay for pusbbutton debounce
int stepperDelay = 7;                 // milliseconds between stepper motor steps
float tubeID = 0.2;
float flowrate = 0.3;
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
  stepper_forward();
  serial_flush_buffer();
  Serial.println("Please enter a tube ID (default 0.2): ");
  tubeID = ui_wait_serial();
  Serial.print("Tune ID = ");
  Serial.println(tubeID);
} // end setup


// ******************* Main Loop ******************
void loop() {

  
  // Check incomming serial
  check_serial();
  
  
  // Check Pushbutton state
  //  and toggle pbLatch
  pbLatch = check_pushbutton(pbLatch);

  // Check if it is time to blink the LED
  // and switch state if enough time has elapsed
  blink_timer(millis(), pbLatch);
  
  // Run stepper motor if PB is latched on
  run_stepper(pbLatch);

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

  //Serial.println(latchValue); // For debugging
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
  pbLastDebounceTime = millis();
  delay(pbDebounceDelay);
  if(digitalRead(PB_PIN)){
    latchValue = !latchValue;
  }
  return latchValue;
}
//
//
//
// ****************** stepper_forward ***************
// Stepper motor step controls
//
void stepper_forward(void){
  digitalWrite(DIR_PIN, LOW);
}
//
//
//
// ****************** stepper_backward **************
// Stepper motor step controls
//
void stepper_backward(void){
  digitalWrite(DIR_PIN, HIGH);
}
//
//
//
// ****************** run_stepper *******************
// Stepper motor step controls
//
void run_stepper(bool latchValue){
  // Run stepper if pushbutton is latched
  //  latchValue is pushbutton state
  if (latchValue){
    digitalWrite(STEP_PIN, HIGH);
    delay(stepperDelay);
    digitalWrite(STEP_PIN, LOW);
    delay(stepperDelay);
  }
}
//
//
// ****************** check_serial *******************
// Check the incomming serial buffer for commands
//
float check_serial(){
  float serValue = 0.0;
  if (Serial.available()){
    // Serial is available
    // Read serial
    serValue = Serial.parseFloat();
    // Clear buffer
    serial_flush_buffer();
    if (serValue==0.0){
      Serial.println("You did not enter a number, please enter the correct datatype");
    }
    else{
      Serial.print("Char recieved: ");
      Serial.println(serValue);
    }
  }
  return serValue;
}
//
// 
// ****************** ui_wait_serial *******************
// Check the incomming serial buffer for commands
//
float ui_wait_serial(){
  float serValue = 0.0;
  while (!Serial.available()){
      // Wait for serial to be available.
    }
  // Serial is available
  // Read serial
  serValue = Serial.parseFloat();
  // Clear buffer
  serial_flush_buffer();
  if (serValue==0.0){
    Serial.println("You did not enter a number, please enter the correct datatype");
  }
return serValue;
}
//
// 

// ****************** serial_flush_buffer *******************
// Flush the serial buffer.
//
void serial_flush_buffer()
{
  while (Serial.read() >= 0)
   ; // do nothing
}
// <<<<<<<<<<<< Sub Functions <<<<<<<<<<<<<<<<<<
