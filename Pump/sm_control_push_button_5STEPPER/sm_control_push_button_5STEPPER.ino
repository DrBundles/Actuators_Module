// DECLARE SWITCH CONTROL
int MOTORStateA = 0;
int buttonPINA = 52;
int buttonNewA;
int buttonOldA = 1;
//B
int MOTORStateB = 0;
int buttonPINB = 50;
int buttonNewB;
int buttonOldB = 1;
//C
int MOTORStateC = 0;
int buttonPINC = 48;
int buttonNewC;
int buttonOldC = 1;
//D
int MOTORStateD = 0;
int buttonPIND = 46;
int buttonNewD;
int buttonOldD = 1;
//E
int MOTORStateE = 0;
int buttonPINE = 44;
int buttonNewE;
int buttonOldE = 1;





// DECLARE MOTOR CONTROL
//A
const int stepsPerRev = 200; //         200/400 depending on stepper motor 
const int stepPinA = 3;
const int dirPinA = 2;
const int MS1A = 4 ;
const int MS2A = 5;
const int MS3A = 6;
//const int ENABLE = 13;

//B
const int stepPinB = 9;
const int dirPinB = 8;
const int MS1B = 10 ;
const int MS2B = 11;
const int MS3B = 12;

//C
const int stepPinC = 23;
const int dirPinC = 22;
const int MS1C = 24 ;
const int MS2C = 25;
const int MS3C = 26;


//D
const int stepPinD = 28;
const int dirPinD = 27;
const int MS1D = 29 ;
const int MS2D = 30;
const int MS3D = 31;

//E
const int stepPinE = 34;
const int dirPinE = 33;
const int MS1E = 35 ;
const int MS2E = 36;
const int MS3E = 37;

void setup() {
Serial.begin(9600); 
pinMode(buttonPINA, INPUT);

   //Declare pins as outputs
pinMode(dirPinA,OUTPUT);
pinMode(stepPinA,OUTPUT);
pinMode(MS1A,OUTPUT);
pinMode(MS2A,OUTPUT);
pinMode(MS3A,OUTPUT);
//pinMode(13,OUTPUT);
//B
pinMode(dirPinB,OUTPUT);
pinMode(stepPinB,OUTPUT);
pinMode(MS1B,OUTPUT);
pinMode(MS2B,OUTPUT);
pinMode(MS3B,OUTPUT);
//C
pinMode(dirPinC,OUTPUT);
pinMode(stepPinC,OUTPUT);
pinMode(MS1C,OUTPUT);
pinMode(MS2C,OUTPUT);
pinMode(MS3C,OUTPUT);
//D
pinMode(dirPinD,OUTPUT);
pinMode(stepPinD,OUTPUT);
pinMode(MS1D,OUTPUT);
pinMode(MS2D,OUTPUT);
pinMode(MS3D,OUTPUT);
//E
pinMode(dirPinE,OUTPUT);
pinMode(stepPinE,OUTPUT);
pinMode(MS1E,OUTPUT);
pinMode(MS2E,OUTPUT);
pinMode(MS3E,OUTPUT);

  //set direction, ENABLE set to LOW--FET OUTPUTS controlled by controller
  digitalWrite(dirPinA, HIGH);  
  //digitalWrite(13, LOW);
  digitalWrite(dirPinB, HIGH);
  digitalWrite(dirPinC, HIGH);
  digitalWrite(dirPinD, HIGH);
  digitalWrite(dirPinE, HIGH);
  
  //sets microstepping resolution to eigth step (see microstepping resolution truth table for A4988 stepper motor controller)
  digitalWrite(MS1A, HIGH);
  digitalWrite(MS2A, HIGH);
  digitalWrite(MS3A, HIGH);
  //B
  digitalWrite(MS1B, HIGH);
  digitalWrite(MS2B, HIGH);
  digitalWrite(MS3B, HIGH);
  //C
  digitalWrite(MS1C, HIGH);
  digitalWrite(MS2C, HIGH);
  digitalWrite(MS3C, HIGH);
  //D
  digitalWrite(MS1D, HIGH);
  digitalWrite(MS2D, HIGH);
  digitalWrite(MS3D, HIGH);
  //E
  digitalWrite(MS1E, HIGH);
  digitalWrite(MS2E, HIGH);
  digitalWrite(MS3E, HIGH);

  //for (int x = 0 ; x < stepsPerRev; x++) {
  //  digitalWrite(stepPin,HIGH);
  //  delay(1);
  //  digitalWrite(stepPin,LOW);
  //  delay(1);
  //}


}

void loop() {

//  
  digitalWrite(stepPinA, HIGH);
  delay(5); // 200/400 steps per rev stepper motor, 4000 microseconds * 2 (low+high) per step
  digitalWrite(stepPinA, LOW);
  delay(5);
  buttonNewA=digitalRead(buttonPINA);

  if(buttonOldA==0 && buttonNewA==1){
    if(MOTORStateA==0){
      pinMode(dirPinA, INPUT);
      pinMode(stepPinA, INPUT);
     
      MOTORStateA=1;
      } 
     else{
      pinMode(dirPinA, OUTPUT);
      pinMode(stepPinA, OUTPUT);
     
      MOTORStateA = 0;
     } 
       
  }

  //  B
  digitalWrite(stepPinB, HIGH);
  delay(5); // 200/400 steps per rev stepper motor, 4000 microseconds * 2 (low+high) per step
  digitalWrite(stepPinB, LOW);
  delay(5);
  buttonNewB=digitalRead(buttonPINB);

  if(buttonOldB==0 && buttonNewB==1){
    if(MOTORStateA==0){
      pinMode(dirPinB, INPUT);
      pinMode(stepPinB, INPUT);
     
      MOTORStateB=1;
      } 
     else{
      pinMode(dirPinB, OUTPUT);
      pinMode(stepPinB, OUTPUT);
     
      MOTORStateA = 0;
     } 
       
  }

  //  C
  digitalWrite(stepPinC, HIGH);
  delay(5); // 200/400 steps per rev stepper motor, 4000 microseconds * 2 (low+high) per step
  digitalWrite(stepPinC, LOW);
  delay(5);
  buttonNewC=digitalRead(buttonPINC);

  if(buttonOldC==0 && buttonNewC==1){
    if(MOTORStateC==0){
      pinMode(dirPinC, INPUT);
      pinMode(stepPinC, INPUT);
     
      MOTORStateC=1;
      } 
     else{
      pinMode(dirPinC, OUTPUT);
      pinMode(stepPinC, OUTPUT);
     
      MOTORStateC = 0;
     } 
       
  }

  //  
  digitalWrite(stepPinD, HIGH);
  delay(5); // 200/400 steps per rev stepper motor, 4000 microseconds * 2 (low+high) per step
  digitalWrite(stepPinD, LOW);
  delay(5);
  buttonNewD=digitalRead(buttonPIND);

  if(buttonOldD==0 && buttonNewD==1){
    if(MOTORStateD==0){
      pinMode(dirPinD, INPUT);
      pinMode(stepPinD, INPUT);
     
      MOTORStateD=1;
      } 
     else{
      pinMode(dirPinD, OUTPUT);
      pinMode(stepPinD, OUTPUT);
     
      MOTORStateD = 0;
     } 
       
  }

  //  E
  digitalWrite(stepPinE, HIGH);
  delay(5); // 200/400 steps per rev stepper motor, 4000 microseconds * 2 (low+high) per step
  digitalWrite(stepPinE, LOW);
  delay(5);
  buttonNewE=digitalRead(buttonPINE);

  if(buttonOldE==0 && buttonNewE==1){
    if(MOTORStateE==0){
      pinMode(dirPinE, INPUT);
      pinMode(stepPinE, INPUT);
     
      MOTORStateE=1;
      } 
     else{
      pinMode(dirPinE, OUTPUT);
      pinMode(stepPinE, OUTPUT);
     
      MOTORStateE = 0;
     } 
       
  }

     buttonOldA = buttonNewA;
     buttonOldB = buttonNewB;
     buttonOldC = buttonNewC;
     buttonOldD = buttonNewD;
     buttonOldE = buttonNewE;
        
  // put your main code here, to run repeatedly:

  //for(int x = 0; x < stepsPerRev; x++)
  //{
//
//  digitalWrite(stepPin, HIGH);
//  delay(5); // 200/400 steps per rev stepper motor, 4000 microseconds * 2 (low+high) per step
//  digitalWrite(stepPin, LOW);
//  delay(5);


  //}
  //delayMicroseconds(2000);
}

// Define pin connections & motor's steps per revolution
//const int dirPin = 3;
//const int stepPin = 4;
//const int stepsPerRevolution = 200;
//
//void setup()
//{
//  // Declare pins as Outputs
//  pinMode(stepPin, OUTPUT);
//  pinMode(dirPin, OUTPUT);
//}
//void loop()
//{
//  // Set motor direction clockwise
//  digitalWrite(dirPin, HIGH);
//
//  // Spin motor slowly
//  for(int x = 0; x < stepsPerRevolution; x++)
//  {
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(2000);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(2000);
//  }
//  delay(1000); // Wait a second
//
//  // Set motor direction counterclockwise
//  digitalWrite(dirPin, LOW);
//
//  // Spin motor quickly
//  for(int x = 0; x < stepsPerRevolution; x++)
//  {
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(1000);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(1000);
//  }
//  delay(1000); // Wait a second
//}
