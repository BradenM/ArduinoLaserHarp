#include <Arduino.h>
#include <sound.h>

// Speaker Vars
const int speak = 3;
const int speed = 90;


void startup(){
  for(int x = 0;x<=4; x++){
    harpPlay(x, 8);
  }
  for(int x = 4;x>=0; x--){
    harpPlay(x, 8);
  }
}

void harpPlay(int opt, int duration){
  int dur = speed*duration;
  switch(opt){
    case 0:
      tone(speak, NOTE_G4, dur*.95);
      delay(dur);
      noTone(speak);
      break;
    case 1:
      tone(speak, NOTE_A4, dur*.95);
      delay(dur);
      noTone(speak);
      break;
    case 2:
      tone(speak, NOTE_B4, dur*.95);
      delay(dur);
      noTone(speak);
      break;
    case 3:
      tone(speak, NOTE_C5, dur*.95);
      delay(dur);
      noTone(speak);
      break;
    case 99:
      startup();
      break;
  }
}
