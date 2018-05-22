#include <Arduino.h>
#include <Stepper.h>
#include <pitches.h>
#include <status.h>
#include <main.h>

// Light Sensor
int lightSensor = A1;
float rawRange = 1024; // 3.3v
float logRange = 5.0; // 3.3v = 10^5 lux
int rawLight = 0;
int lightRead = 0;
int sensorTrig = 75;


// Harp Settings
bool harpStatus = true;
int direction = 1;
const int notes = 4;
int noteCount = 0;
const int noteSpace = 16;
bool position = false;
int start_adjust = -2;
int beamDelay = 15;

// Laser
const int beamPin = 7;

// Stepper
const int revSteps = 16;
Stepper harpStepper(revSteps, 8, 10, 9, 11);


float RawToLux(int raw)
{
  float logLux = raw * logRange / rawRange;
  return pow(10, logLux);
}

void setup() {
  setStatus(false);
  if (position == true){
    //beamDelay = 100;
  }
  analogReference(EXTERNAL);
  pinMode(beamPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(controlPin, INPUT);
  harpStepper.setSpeed(2500);
  Serial.begin(9600);
  harpStepper.step(noteSpace * start_adjust);
  digitalWrite(beamPin, HIGH);
  delay(8000);
  digitalWrite(beamPin, LOW);
  setStatus(true);

}

void loop() {
//   if (harpStatus == false){
//     while(harpStatus == false){
//       setStatus(false);
//       harpStatus = checkControl(harpStatus);
//       Serial.println(harpStatus);
//       digitalWrite(beamPin, HIGH);
//       if(harpStatus == false){
//         harpStepper.step(noteSpace * (noteCount * direction));
//         Serial.println("ADJUSTED!!");
//         noteCount = 0;
//         direction = 1;
//       }
//     }
// }
  //harpStatus = checkControl(harpStatus);
  harpStepper.step(noteSpace * direction);
  noteCount += direction;
  digitalWrite(beamPin, HIGH);
  rawLight = analogRead(lightSensor);
  lightRead = RawToLux(rawLight);
  //Serial.println(lightRead);
  // if(rawLight > sensorTrig){
  //   Serial.println(rawLight);
  //   Serial.print("BREAK AT: ");
  //   Serial.print(noteCount);
  // }
  Serial.println(rawLight);
  //Serial.println(noteCount);
  delay(beamDelay);
  digitalWrite(beamPin, LOW);

  if((noteCount == 0 || noteCount == notes) && position == false){
    direction *= (-1);
  }

}
