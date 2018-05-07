#include <Arduino.h>
#include <Stepper.h>

// Constants
const int revSteps = 64;
const int notes = 6;

// Steppers
Stepper mirStepper(revSteps, 8, 9, 10, 11);

void setup() {
  mirStepper.setSpeed(450);
}

void runMirror(int steps){
  for(int x=0; x<=notes; x++){
    mirStepper.step(steps);
    Serial.println('Completed Clockwise');
    delay(15);
  }
  delay(15);
}


void loop() {
  runMirror(revSteps);
  runMirror(-revSteps);

}
