// BIOE 3090: Module 3 - Arduino 
// Shreemathi Harikrishnan

/* This code is designed to take in an input of flow rate [cm^3/min] and tube diameter [cm], 
 * and spin a micropump accordingly. If no value is inputed in the Serial montior when prompted 
 * then the code automatically sets the default values to 1 [cm^3/min] and 0.2 [cm]. There is 
 * a green light flashing when the pump is running and it will cease to blink when the pump 
 * is not running. If the flow rate is decreased or the diameter is increased, the rotation 
 * speed of the pump will reduce according to the calculations to maintain the flow rate. 
 * And if the flow rate is increased or the diameter is decreased, the rotation speed of 
 * the pump will reduce according to the calculations to maintain the flow rate. 
 * 
 * For Testing: Fist I will let the code run with the default values. Then, I will be lowering 
 * and heightning both values while keeping the other at its default. Then I will enter a value 
 * for both inputs to show that the code can take 2 inputs. 
 */
 
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Pin Definitions >>>>>>>>>>>>>>>>>>>>>>>>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define LED_PIN 13 //int ledPin = 13;
#define PB_PIN 12
#define STEP_PIN 8 
#define DIR_PIN 9 


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Globals >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

bool ledState = false;
double lastTime = 0;              // milliseconds, holds time value during main loop
unsigned long currentTime = 0;    // milliseconds 
unsigned long switchTime = 500;   // how fast  LED on and off
bool pbLatch = false;             // boolean latch
unsigned long pbLastDebounceTime = 0;
unsigned long pbDebounceDelay = 50;
int stepperDelay = 5;             // How fast it motor spins 
double flowRate;
double tubeDia;
double pi = 3.1415;
double vel;                      // velocity
double stepperDelayNew;          // after input motor turning speed
bool didUiWork = false;          // set to false at first to run in mail loop

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SetUp >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_PIN, OUTPUT);
  pinMode(PB_PIN, INPUT);
  // initialize timers for LED blinking
  lastTime = millis();
  currentTime = lastTime;
  stepper_forward();
}


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Main Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void loop() {

  // didUiWork is set to false so immedietly go to userInputs
  if (didUiWork == false) {
       userInputs();
  }
  
   pbLatch = check_pushbutton(pbLatch); // check push button & toggle pbLatch
   blink_timer(millis(), pbLatch); /* Check if its time to blink the LED
   and switch state if enough time has elapsed */
   run_stepper(pbLatch);
} 


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Sub Functions >>>>>>>>>>>>>>>>>>>>>>>>>>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void blink_led(int ledPin, bool ledOnOff){
  digitalWrite(ledPin, ledOnOff);   // turn the LED on (HIGH is the voltage level)
}

//---------------------------------------------------------------------------

void blink_timer(unsigned long currentTime, bool pbLatch){

  if ((currentTime - lastTime) >= switchTime) {
    lastTime = currentTime;
    // Switch LED state if bBlink was triggered by timing loop
    if(pbLatch){
     ledState = !ledState;
     blink_led(LED_PIN, ledState);
    }
  }
}

//---------------------------------------------------------------------------

bool check_pushbutton(bool latchValue) { // check push button & toggle pbLatch
  
 if (digitalRead(PB_PIN)){ // Poll state of the pushbutton, debounce if siganl is there
  latchValue = pb_debounce(latchValue); 
    while(digitalRead(PB_PIN)){  
    }
 }
// Turn off LED if latchValue is false or it could be not blinking but be on
 if (latchValue == false){ 
  digitalWrite(LED_PIN, false);
 }
// Serial.println(latchValue);
 return latchValue;
}

//---------------------------------------------------------------------------

bool pb_debounce(bool latchValue) {
  pbLastDebounceTime = millis();
  delay(pbDebounceDelay);
  if(digitalRead(PB_PIN)) {
    latchValue = !latchValue;    // this step is where the light is switched off 
  }
  return latchValue;
}

//---------------------------------------------------------------------------

void stepper_forward(void){
  digitalWrite(DIR_PIN, HIGH);
}

//---------------------------------------------------------------------------

void stepper_backward(void){
  digitalWrite(DIR_PIN, LOW);
}

//---------------------------------------------------------------------------

void run_stepper(bool latchValue){
  if (latchValue){ // run if pb is latched 
  digitalWrite(STEP_PIN, HIGH);
  delay(stepperDelay);
  digitalWrite(STEP_PIN, LOW);
  delay(stepperDelayNew);

  }
}

void userInputs() {  
// Take user input for flowrate  
Serial.println("Provide flow rate in [cm^3/min]:  ");
while(!Serial.available()) {
  } // waiting for user input 
if(Serial.available() > 0) {
  flowRate = (Serial.parseFloat());
   Serial.print(flowRate);
   Serial.print(" [cm^3/min] ");
   Serial.println("");

   flowRate = flowRate/60; // need it per sec
   Serial.read(); // so it doesn't lag, discards rest of buffer
}

// Set to Deafult for Flow Rate
if (flowRate == 0){
   flowRate = 1;
   Serial.println("No input given. Default Flow rate set to 1 [cm^3/min].");
   flowRate = flowRate/60;
}

// Take user input for tube diameter 
Serial.println("Provide tube diameter in [cm]:  ");
while(!Serial.available()) {} // waiting for user input 
if(Serial.available() > 0) {
  tubeDia = (Serial.parseFloat());
   Serial.print(tubeDia);
   Serial.print(" [cm] ");
   Serial.println("");
}

// Set to Deafult value if no values are inserted
if (tubeDia == 0){
   tubeDia = 0.2;
   Serial.println("No input given. Default tube diameter set to 0.2 [cm].");
   Serial.println("");
}

Serial.println("The Pump rate has been adjusted accordingly.");

didUiWork = true; // yay UI ran!!

// Mathamatics to set pump speed 
vel = (4*flowRate)/(pi*tubeDia*tubeDia);
stepperDelayNew = (((2*pi)/200)/vel)*1000;
stepperDelayNew = stepperDelayNew/2;

}
