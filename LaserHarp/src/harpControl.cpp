#include <Arduino.h>

void checkBeams(int notes, int beamReadings[], int sensorThreshold, int sensorToss){
  for(int stringTest=0; stringTest < notes+1; stringTest++){
    //Serial.println("-------");
    for(int compStr=0; compStr < notes+1; compStr++){
      int diff = beamReadings[stringTest] - beamReadings[compStr];
      if(diff > sensorThreshold && diff < sensorToss){
        //Serial.println("STRING DIFF: ");
        Serial.println(diff);
        Serial.println("break at beam: ");
        //Serial.println(stringTest);
      }
    }
    //Serial.println("-------");
  }
}
