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
int sensorThreshold = 43;
int sensorToss = 400;
int curLight = 0;


// Ultrasonic
const int uTrig = 5;
const int uEcho = 4;
long duration;
long distance;
bool player = false;


// Harp Settings
int direction = 1;
const int notes = 2; // (plus one)
int noteCount = 0;
bool isHome = true;
const int noteSpace = 16;
int beamDelay = 12;
int motorDelay = 3;
int coolDown = 30;

// Debug
bool position = false;
bool debug_mode = false;
bool find_ldr = false;
int start_adjust = -2;
int LDRtest = 0;

// Laser and Readings
const int beamPin = 7;
int beamCount = 0;
int baseReadings[4] = {0, 0, 0, 0};
int beamReadings[4] = {0, 0, 0, 0};
bool beamActive = false;


// Stepper
const int revSteps = 16;
Stepper harpStepper(revSteps, 8, 10, 9, 11);


void setup() {
  setStatus(STANDBY);
  //analogReference(EXTERNAL);
  pinMode(beamPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(controlPin, INPUT);
  pinMode(uTrig, OUTPUT);
  pinMode(uEcho, INPUT);
  harpStepper.setSpeed(2500);
  Serial.begin(9600);
  delay(100);
  //harpPlay(STARTUP, 2);
  if (position == true){
    delay(2500);
    harpStepper.step(noteSpace * start_adjust);
    digitalWrite(beamPin, HIGH);
    while(1){
      delay(100);
    }
  }

}


int getPlayer(){
  digitalWrite(uTrig, LOW);
  delayMicroseconds(2);

  digitalWrite(uTrig, HIGH);
  delayMicroseconds(2);
  digitalWrite(uTrig, LOW);

  duration = pulseIn(uEcho, HIGH);
  distance = duration*0.032/2;
  // if(distance < 100){
  //   return true;
  // }else{
  //   return false;
  // }
  return distance;
}

void debug(){
  setStatus(ACTIVE);
  digitalWrite(beamPin, HIGH);
  while(1){
  LDRtest = analogRead(lightSensor);
  int player = getPlayer();
  Serial.println(LDRtest);
  //Serial.println(player);
  delay(100);
}
}

void stopHarp(){
  harpStatus = false;
  Serial.print("LOWER CALLED");
  delay(1000);
  if(noteCount == 0){
    isHome = true;
    direction = 1;
    beamCount = 0;
    for(int x = 0; x < 4; x++){
      beamReadings[x] = 0;
    }
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
  if(debug_mode == true){
    debug();
  }
  if(harpStatus == false){
    //Serial.print("CALLED");
    setStatus(READY);
    while(harpStatus == false){
      delay(100);
      if(debug_mode == true){
        digitalWrite(beamPin, HIGH);
      }
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
    coolDown--;
    //Serial.println(coolDown);
    beamActive = false;
    isHome = false;
    if(beamCount >=notes+1){
      beamCount = 0;
    }

    // Turn Beam on and collect reading
    digitalWrite(beamPin, HIGH);
    // player = getPlayer();
    // Serial.println(player);
    curLight = analogRead(lightSensor);
    if(find_ldr==true){
      Serial.println(curLight);
      beamActive = true;
    }
    if(curLight > sensorThreshold && beamActive == false && coolDown <= 0){
        Serial.println(curLight);
        //harpPlay(beamCount, 4);
        Serial.println("music called");
        coolDown = 30;
        beamActive = true;
        harpPlay(beamCount, 4);
        harpPlay(0);
    }
    delay(beamDelay);
    digitalWrite(beamPin, LOW);

    // Continue to next step
    harpStepper.step(noteSpace * direction);
    delay(motorDelay);
    noteCount += direction;
    beamCount++;

    // Set to turn around if at end of fan
    if(noteCount == 0 || noteCount == notes){
      direction *= (-1);
    }

    // Watch for button press to turn off
    if (digitalRead(controlPin) == HIGH){
      stopHarp();
      for(int x=0; x<=3; x++){
        //Serial.println(beamReadings[x]);
      }
      Serial.println("sizeof: ");
    }
}

}
