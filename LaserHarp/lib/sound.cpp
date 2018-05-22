#include <Arduino.h>
#include"pitches.h"

int melody[] = {
  NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
};

int duration[] = {
  8
};

int speed=90;

void setup() {
  Serial.begin(9600);

}

void loop() {
  delay(500);
  for (int thisNote = 0; melody[thisNote]!=-1; thisNote++){
    int noteDuration = speed*duration[thisNote];
    tone(3, melody[thisNote], noteDuration*.95);
    Serial.println(melody[thisNote]);
    delay(noteDuration);
    noTone(3);

  }

}
