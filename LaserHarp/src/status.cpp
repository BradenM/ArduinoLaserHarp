#include <Arduino.h>
#include <status.h>

int buttonState = 0;
int prevState = 0;
int buttonCount = 0;

void setStatus(bool status)
{
  if(status == true){
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
  }
  else{
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
  }
}

bool checkControl(bool curState){
  int controlState = digitalRead(controlPin);
  if (controlState != prevState){
    if (controlState == HIGH){
      buttonCount++;
      Serial.println("STATE HIGH");
    }
    else{
      Serial.println("BUTTON STATE LOW");
    }
    delay(50);
  }
  prevState = controlState;

if (buttonCount % 2 == 0) {
  return curState;
} else {
  return !curState;
}

}
