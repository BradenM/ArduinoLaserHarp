#include <Arduino.h>
#include <Stepper.h>
#include <status.h>
#include <sound.h>
#include <harpControl.h>
#include <main.h>

// Light Sensor
int lightSensor = A1;
float rawRange = 1024; // 3.3v
float logRange = 5.0; // 3.3v = 10^5 lux
int rawLight = 0;
int lightRead = 0;
int sensorThreshold = 40;
int sensorToss = 100;
int curLight = 0;


// Harp Settings
int direction = 1;
const int notes = 3; // (plus one)
int noteCount = 0;
bool isHome = true;
const int noteSpace = 16;
bool position = false;
int start_adjust = -1;
int beamDelay = 8;

// Laser and Readings
const int beamPin = 7;
int beamCount = 0;
int baseReadings[4] = {0, 0, 0, 0};
int beamReadings[4] = {0, 0, 0, 0};


// Stepper
const int revSteps = 16;
Stepper harpStepper(revSteps, 8, 10, 9, 11);


void setup() {
  setStatus(STANDBY);
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
  if (position == true){
    digitalWrite(beamPin, HIGH);
    while(1){
      delay(100);
    }
  }
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
    harpStepper.step(noteSpace * direction);
    digitalWrite(beamPin, HIGH);
    curLight = analogRead(lightSensor);
    beamReadings[beamCount] = curLight;
    noteCount += direction;
    delay(beamDelay);
    digitalWrite(beamPin, LOW);

    if(noteCount == 0 || noteCount == notes){
      direction *= (-1);
    }
    if(beamCount>=4){
      beamCount=0;
    }else{
      beamCount++;
    }

    if (digitalRead(controlPin) == HIGH){
      stopHarp();
      for(int x=0; x<=3; x++){
        Serial.println(beamReadings[x]);
      }
      Serial.println("sizeof: ");
    }

  checkBeams(notes, beamReadings, sensorThreshold, sensorToss);
}

}
