#include <Arduino.h>

int delta = 30;
bool plucked = false;

void checkBeams(int notes, int beamReadings[], int sensorThreshold, int sensorToss){
  for(int stringTest=0; stringTest < notes; stringTest++){
    //Serial.println("-------");
    for(int compStr=0; compStr < notes; compStr++){
      int diff = beamReadings[stringTest] - beamReadings[compStr];
      //Serial.println(diff);
      if(diff > sensorThreshold){
        //Serial.println("STRING DIFF: ");
        Serial.println(diff);
        Serial.println("break at beam: ");
        Serial.println(stringTest);
      }
    }
    //Serial.println("-------");
  }
}

void tellBeams(int beamReadings[]){
  for(int x=0; x <=3; x++){
    Serial.println(beamReadings[x]);
  }
}

void compareBeam(int beam, int beamReadings[]){
  for(int x=0; x <=3; x++){
    int diff = beamReadings[beam] - beamReadings[x];
    // Serial.println("BEAM: ");
    // Serial.println(beam);
    // Serial.println("DIFF VALS: ");
    // Serial.println(diff);
    // Serial.println("------");
    if (diff > delta){
      // Serial.print(beam);
      // Serial.println(" is broken");
      // Serial.println("With value:");
      // Serial.print(diff);
      // Serial.println();
      plucked = true;
    }
  }
  if(plucked = true){
    Serial.print(beam);
    Serial.println(" is broken");
    // Serial.println("With value:");
    // Serial.print(diff);
    Serial.println();
  }
}
