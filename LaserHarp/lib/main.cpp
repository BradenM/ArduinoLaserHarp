#include <Arduino.h>
#include <AccelStepper.h>
#define HALFSTEP 8

// Constants
const int revSteps = 64;
const int notes = 6;

// Stepper
int m1 = 8;
int m2 = 9;
int m3 = 10;
int m4 = 11;
AccelStepper mirStepper(AccelStepper::FULL4WIRE, m1, m2, m3, m4);

void setup() {
  mirStepper.setMaxSpeed(1000);
  mirStepper.setAcceleration(100);
  mirStepper.moveTo(4000);
}

// void runMirror(int steps){
//   for(int x=0; x<=notes; x++){
//     mirStepper.step(steps);
//     Serial.println('Completed Clockwise');
//     delay(15);
//   }
//   delay(15);
// }


void loop()
{
    // If at the end of travel go to the other end
    if (mirStepper.distanceToGo() == 0)
      mirStepper.moveTo(-mirStepper.currentPosition());
    mirStepper.run();
}
