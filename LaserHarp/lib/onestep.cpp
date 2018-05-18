#include <Arduino.h>

int delaymotor = 15;

// Stepper
int m1 = 8;
int m2 = 10;
int m3 = 9;
int m4 = 11;

// Light Sensor
int lightSensor = A0;
float rawRange = 1024; // 3.3v

void setup(){
  analogReference(EXTERNAL);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  //int rawLight = analogRead(lightSensor);
  //Serial.print(rawLight);

  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
  delay(delaymotor);

  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
  delay(delaymotor);

  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
  delay(delaymotor);

  digitalWrite(m1, HIGH);             // Move the motor to create the second beam.( One step forward)
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
  delay(delaymotor);

  // SWAP

  digitalWrite(m1, LOW);             // Move the motor to create the second beam.( One step forward)
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
  delay(delaymotor);

  digitalWrite(m1, LOW);             // Move the motor to create the second beam.( One step forward)
  digitalWrite(m2, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
  delay(delaymotor);

  digitalWrite(m1, LOW);             // Move the motor to create the second beam.( One step forward)
  digitalWrite(m2, HIGH);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
  delay(delaymotor);

  digitalWrite(m1, HIGH);             // Move the motor to create the second beam.( One step forward)
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
  delay(delaymotor);


}
