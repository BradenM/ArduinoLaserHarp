#include <Arduino.h>
#include <Stepper.h>
#include <status.h>
#include <sound.h>
#include <main.h>

// Light Sensor
int lightSensor = A1;
float rawRange = 1024; // 3.3v
float logRange = 5.0; // 3.3v = 10^5 lux
int rawLight = 0;
int lightRead = 0;
int sensorTrig = 25;


// Harp Settings
int direction = 1;
const int notes = 3; // (plus one)
int noteCount = 0;
bool isHome = true;
const int noteSpace = 16;
bool position = false;
int start_adjust = 5;
int beamDelay = 8;

// Laser and Readings
const int beamPin = 7;
int baseReadings[] = {};
int beamReadings[] = {};


// Stepper
const int revSteps = 16;
Stepper harpStepper(revSteps, 8, 10, 9, 11);


void setup() {
  setStatus(STANDBY);
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
  delay(100);
  //harpPlay(STARTUP, 2);
}

void collectBase(){
  setStatus(ACTIVE);
  for(int x=0; x<=3; x++){
    harpStepper.step(noteSpace * direction);
    digitalWrite(beamPin, HIGH);
    noteCount += direction;
    delay(3000);
    digitalWrite(beamPin, LOW);
    baseReadings[x] = analogRead(lightSensor);
    Serial.println(baseReadings[x]);
  }
  for(int x=0; x<=2; x++){
    digitalWrite(beamPin, HIGH);
    harpStepper.step(noteSpace * -1);
    delay(3000);
  }
  delay(10000);
  digitalWrite(beamPin, LOW);

}

void stopHarp(){
  harpStatus = false;
  Serial.print("LOWER CALLED");
  delay(1000);
  if(noteCount == 0){
    isHome = true;
    direction = 1;
  }
  else{
    setStatus(STANDBY);
    while(noteCount != 0){
      harpStepper.step(noteSpace * direction);
      noteCount += direction;
      Serial.println(noteCount);
      Serial.println("ADJUSTED");
      delay(300);
      if(noteCount == 0 || noteCount == notes){
        direction *= (-1);
      }
    }
  }
  Serial.println("STOPPING HARP.");
  delay(500);
}

void loop() {
  if(harpStatus == false){
    delay(3000);
    collectBase();
    delay(10000);
    Serial.print("CALLED");
    setStatus(READY);
    while(harpStatus == false){
      delay(100);
      Serial.println();
      digitalWrite(beamPin, HIGH);
      if(digitalRead(controlPin) == HIGH){
        harpStatus = true;
        setStatus(ACTIVE);
        digitalWrite(beamPin, LOW);
        delay(1500);
        break;
      }
    }
  }
  else{
    isHome = false;
    //harpStatus = checkControl();
    harpStepper.step(noteSpace * direction);
    digitalWrite(beamPin, HIGH);
    noteCount += direction;
    delay(beamDelay);
    digitalWrite(beamPin, LOW);
    rawLight = analogRead(lightSensor);

    if(noteCount == 0 || noteCount == notes){
      direction *= (-1);
    }

    //Serial.println("ORIG NOTECOUNT: ");
    //Serial.print(noteCount);
    //delay(10000);
    //Serial.println(lightRead);
    if(int(rawLight) >= sensorTrig){
      Serial.println(rawLight);
      Serial.print("BREAK AT: ");
      Serial.print(noteCount);
      harpPlay(noteCount, 8);
    }
    //Serial.println(rawLight);
    //Serial.println(noteCount);

    if (digitalRead(controlPin) == HIGH){
      stopHarp();
    }

}

}
