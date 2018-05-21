#include <Arduino.h>
#include <Stepper.h>

// Light Sensor
int lightSensor = A0;
float rawRange = 1024; // 3.3v
float logRange = 5.0; // 3.3v = 10^5 lux


// Harp Settings
int direction = 1;
const int notes = 4;
int noteCount = 0;
const int noteSpace = 16;
const int beamDelay = 7;

// Laser
const int beamPin = 7;

// Stepper
const int revSteps = 16;
Stepper harpStepper(revSteps, 8, 10, 9, 11);


void setup() {
  //analogReference(EXTERNAL);
  pinMode(beamPin, OUTPUT);
  harpStepper.setSpeed(2500);
  Serial.begin(9600);
}

float RawToLux(int raw)
{
  float logLux = raw * logRange / rawRange;
  return pow(10, logLux);
}

void loop() {
  harpStepper.step(noteSpace * direction);
  noteCount += direction;
  digitalWrite(beamPin, HIGH);
  int rawLight = analogRead(A0);
  int lightRead = RawToLux(rawLight);
  //Serial.println(lightRead);
  Serial.println(rawLight);
  delay(beamDelay);
  digitalWrite(beamPin, LOW);

  if(noteCount == 0 || noteCount == notes){
    direction *= (-1);
  }

}
