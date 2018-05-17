#include <Arduino.h>
#include <AccelStepper.h>
#define HALFSTEP 8
#define FULLSTEP 4

// Constants
const int revSteps = 64;
const int notes = 6;
int inc = 200;

// Stepper
int m1 = 8;
int m2 = 9;
int m3 = 10;
int m4 = 11;
AccelStepper mirStepper(AccelStepper::FULL4WIRE, m1, m2, m3, m4);

void setup() {
  mirStepper.setMaxSpeed(4000);
  mirStepper.setAcceleration(2000);
  //mirStepper.moveTo(400);
  Serial.begin(9600);
}

// void runMirror(int steps){
//   for(int x=0; x<=notes; x++){
//     mirStepper.step(steps);
//     Serial.println('Completed Clockwise');
//     delay(15);
//   }
//   delay(15);
// }

void mirMove(int pos, int diff){
  int cPos = pos - diff;
  mirStepper.moveTo(pos);
  while(mirStepper.currentPosition() != cPos){
    mirStepper.run();
  }
  mirStepper.stop();
  mirStepper.runToPosition();
}

void enableBeams(){
  for(int x = 0; x <= 5; x++){
    Serial.print(inc);
    Serial.print("\n");
    mirMove(inc, 200);
    inc = inc + 300;
    delay(500);
  }
}

void loop() {
    // If at the end of travel go to the other end
    // if (mirStepper.distanceToGo() == 0)
    //   mirStepper.moveTo(-mirStepper.currentPosition());
    // mirStepper.run();

    enableBeams();
    //Serial.print('Done');

}
