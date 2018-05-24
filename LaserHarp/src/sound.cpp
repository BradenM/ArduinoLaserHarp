#include <Arduino.h>
#include <sound.h>

// Speaker Vars
int speed = 90;


void startup(){
  speed = 40;
  for(int x = 0;x<=4; x++){
    harpPlay(x, 4);
  }
  for(int x = 4;x>=0; x--){
    harpPlay(x, 4);
  }
  speed = 90;
}

void harpPlay(int opt, int duration=8){
  int dur = speed*duration;
  switch(opt){
    case 0:
      noTone(speak);
      break;
    case 1:
      tone(speak, NOTE_G4, dur*.95);
      delay(dur);
      noTone(speak);
      break;
    case 2:
      tone(speak, NOTE_A4, dur*.95);
      delay(dur);
      noTone(speak);
      break;
    case 3:
      tone(speak, NOTE_B4, dur*.95);
      delay(dur);
      noTone(speak);
      break;
    case 4:
      tone(speak, NOTE_C5, dur*.95);
      delay(dur);
      noTone(speak);
      break;
    case 99:
      startup();
      break;
  }
}
