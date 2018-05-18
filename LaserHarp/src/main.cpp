#include <Arduino.h>
#include <AccelStepper.h>
#define HALFSTEP 8
#define FULLSTEP 4

// Light Sensor
int lightSensor = A0;
float rawRange = 1024; // 3.3v

// Constants
const int notes = 6;
int inc = 8;
int mod = 8;

// Stepper
int m1 = 8;
int m2 = 9;
int m3 = 10;
int m4 = 11;
AccelStepper mirStepper(FULLSTEP, m1, m3, m2, m4);
float logRange = 5.0; // 3.3v = 10^5 lux

void setup() {
  analogReference(EXTERNAL);
  mirStepper.setMaxSpeed(6000);
  mirStepper.setAcceleration(6000);
  Serial.begin(9600);
}

float RawToLux(int raw)
{
  float logLux = raw * logRange / rawRange;
  return pow(10, logLux);
}

void enableBeams(){

  for(int x = 0; x <= notes; x++){
    mirStepper.runToNewPosition(inc);
    inc = inc + mod;
    mirStepper.stop();
    int rawLight = analogRead(A0);
    int light = RawToLux(rawLight);
    if(light >= 150){
      Serial.println("BREAK ON - ");
      Serial.print(mod);
    }
    Serial.println(light);
    delay(8);
  }
  if(mod > 0){
    mod = -8;
  }else{
    mod = 8;
  }
}

void loop() {
    enableBeams();



}
