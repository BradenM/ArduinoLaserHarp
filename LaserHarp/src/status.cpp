#include <Arduino.h>
#include <status.h>

int newState;
int prevState = LOW;
int buttonCount = 0;
extern bool harpStatus;
long time;
long debounce = 200;

void setStatus(int status)
{
  switch(status){
    case 0:
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      break;
    case 1:
      analogWrite(redPin, 0);
      analogWrite(greenPin, 255);
      break;
    case 2:
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
  }
}

bool checkControl(){
  int controlState = digitalRead(controlPin);
  if (controlState == HIGH && prevState == LOW && millis() - time > debounce){
    if (controlState == HIGH){

    }
    else
      newState = !harpStatus;
    }
  time = millis();
  prevState = controlState;
  return newState;
}
