/*
  This code controls the micropump with a pushbutton. As the pushbutton is pressed
  the motor will start rotating and the LED will start blinking, and when the button 
  is pressed again, the motor will stop and the LED will turn off. Moreover, the user
  can input different flow rates and tube diameters and the steps of the motor will be
  adjusted accordingly.To improve the user experience we added a tri color LED that turns
  red when the motor in turned off and green when it is on. 

  Turns an LED on for one second, then off for one second, repeatedly.

  Pin 13 – Digital out: LED

  created 25 Feburary 2020
  by Steve Lammers
  Updated: 6 April 2020
  by Miray Elkedwani
  
  This example code is in the public domain.

  Source code adapted from - http://www.arduino.cc/en/Tutorial/Blink
*/

// >>>>>>>>>>> Pin Definitions >>>>>>>>>>>>>>>>>>
#define RED_PIN 5        //Red LED control
#define GREEN_PIN 6        //Green LED control
#define BLUE_PIN 7        //Blue LED control   
#define PB_PIN 12         //Pushbutton
#define STEP_PIN 8        //Stepper driver steps once on low to high transition
#define DIR_PIN 9         // Sets stepper motor direction on stepper driver
#define pi 3.14159265359  // setting pi value for calculations
// <<<<<<<<<<< Pin Definitions <<<<<<<<<<<<<<<<<<


// >>>>>>>>>>> Globals >>>>>>>>>>>>>>>>>>>>>>>>>>
bool ledState = false;                  // Boolean latch for LED status
bool pbLatch = false;                   // Boolean latch for controlling LED blink
bool UserInputs = false;                // Boolean latch asl=king for user inputs
bool MotorState = true;                 // Boolean latch for stepper motor status
double lastTime = 0;                    // milliseconds, holds time value during main loop
double lastTimeMotor = 0;               // milliseconds, holds last time for motor
double FlowRate;                        // User input for flow rate
double TubeDiameter;                    // User input for tube diameter
double AngularVelocity;                // Angular Velocity for pump (calculation)
unsigned long currentTime = 0;          // milliseconds 
unsigned long switchTime = 1000;        // milliseconds between blinking LED on and off
unsigned long stepperDelay = 5;    // milliseconds between stepper motor steps
unsigned long pbLastDebounceTime = 0;   // milliseconds time of last pb press
unsigned long pbDebounceDelay = 50;     // milliseconds delay for pushbutton
//int stepperDelay=5;                     // milliseconds between motor steps
// <<<<<<<<<<< Globals <<<<<<<<<<<<<<<<<<<<<<<<<<


// ******************* Setup *********************
// the setup function runs once when you press reset or power the board
void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // initialize digital the LEDS as an inputs and pushbutton as output.
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(PB_PIN, INPUT);
  
  // initialize timers for LED blinking
  lastTime = millis();
  currentTime = lastTime;
  stepper_forward();
} // end setup


// ******************* Main Loop ******************
void loop() {

  //The micropump won't work and will go directly to user inputs
  if (UserInputs == false){
  user_inputs();
}
  // Check Pushbutton State
  // and toggle pbLatch
  pbLatch=check_pushbutton(pbLatch);

  // Run stepper motor if PB is latched on
  run_stepper(pbLatch);
  
} // end loop


// >>>>>>>>>>> Sub Functions >>>>>>>>>>>>>>>>>>
//
//
// ****************** Green and red LED colors ***************
//   LED will turn red when the motor is off and green when the button 
//   is pushed and the motor is rotating
//   
bool check_pushbutton(bool latchValue) { // check push button & toggle pbLatch
  
 if (digitalRead(PB_PIN)){ // Poll state of the pushbutton, debounce if siganl is there
  latchValue = pb_debounce(latchValue); 
    while(digitalRead(PB_PIN)){  
    }
 }
// Turns the LED red if latchValue is false 
 if (latchValue == false){ 
  digitalWrite(RED_PIN, HIGH);
   digitalWrite(GREEN_PIN, LOW);
   digitalWrite(BLUE_PIN, LOW);
 }
// Serial.println(latchValue);
 return latchValue;
}

//

// Turns green LED on when the button is pushed
bool pb_debounce(bool latchValue) {
  pbLastDebounceTime = millis();
  delay(pbDebounceDelay);
  if(digitalRead(PB_PIN)) {
    latchValue = !latchValue;
    digitalWrite(GREEN_PIN, HIGH);
   digitalWrite(RED_PIN, LOW);
   digitalWrite(BLUE_PIN, LOW);
  }
  return latchValue;
}

// ****************** stepper_forward ***************
// Stepper motor step controls
//
void stepper_forward(void){
  digitalWrite(DIR_PIN, HIGH);
}
//
//   
// ****************** stepper_backward ***************
// Stepper motor step controls
void stepper_backward(void){
  digitalWrite(DIR_PIN, LOW);
}
//   
// ****************** run_stepper ***************
// Stepper motor step controls
//
void run_stepper(bool latchValue){
  //Run stepper if pushbutton is latched
  // latchValue is pushbutton state
  if (latchValue){
    digitalWrite(STEP_PIN, HIGH);
    delay(stepperDelay);
    digitalWrite(STEP_PIN, LOW);
    delay(stepperDelay);
  }
}
//
//
// ****************** user_inputs ***************
// Ask user to input flow rate and tube diameter and it automatically adjusts the angular velocity
void user_inputs(){
  Serial.println("Please input flowrate (in cm^3/min) and tube diameter (in cm)");
  Serial.print("Volumetric Flowrate = ");
  while(!Serial.available()) {} //waits for user input
  if(Serial.available() > 0){ //gets an input from the user
     FlowRate = (Serial.parseFloat()); //set variables to floats
     Serial.print(FlowRate); //print flowrate value to serial monitor
     Serial.println (" cm^3/min ");  
     FlowRate = FlowRate/60; //setting flowrate (in seconds)
     Serial.read(); // throw the rest of the buffer
  }
  Serial.print("Tubing Diameter = ");
  while(!Serial.available()) {} //waits for user input
  if(Serial.available() > 0){ //gets an input from the user
     TubeDiameter = Serial.parseFloat(); //set variables to floats
     Serial.print(TubeDiameter); //print tube diameter value to serial monitor
     Serial.println (" cm "); 
}

//Setting Defults if user didn't put any input
//if the user didn't input any value for flow rate it will automatically go to the default
if(FlowRate == 0){
  FlowRate = 1;
  Serial.println("No input for flow rate, setting to default = 1 cm^3/min");
  FlowRate = FlowRate/60; //seting flow rate to 1 cm^3/min (in seconds) 
}
//if the user didn't input any value for the tube diameter it will automatically go to the default
if(TubeDiameter == 0){
  Serial.println("No input for tube diameter, setting to default = 0.2 cm");
  TubeDiameter = 0.2; //setting tube diameter to 0.2 cm (given tube size)
}

// Prints to let user know that the pump is ready to use
Serial.println("");
Serial.println("Flow rate and tube diameters are set");
Serial.println("Micropump is ready, push the button");

//Calculations

AngularVelocity = ((4*FlowRate)/(pi*TubeDiameter*TubeDiameter))/1.8; // angular velocity (rads/sec), 1.8 = radius of pump in cm
stepperDelay = (((2*pi)/200)/AngularVelocity)*1000;   // milliseconds per steps 
stepperDelay = stepperDelay/2;  // dividing total time by 2

UserInputs = true;  //function runs once only
}
// <<<<<<<<<<<< Sub Functions <<<<<<<<<<<<<<<<<<
