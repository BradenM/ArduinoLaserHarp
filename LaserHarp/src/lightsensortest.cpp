 #include <Arduino.h>

int sensorPin = A0;
float rawRange = 1024; // 3.3v
float logRange = 5.0; // 3.3v = 10^5 lux

// Calc Lux Average
float luxAvg[10];

void setup()
{
  pinMode(13, OUTPUT);
  analogReference(EXTERNAL); //
  Serial.begin(9600);
}

float RawToLux(int raw)
{
  float logLux = raw * logRange / rawRange;
  return pow(10, logLux);
}

float collectAvg(){
  for(int y=0;y<=10;y++){
  int rawVal = analogRead(sensorPin);
  luxAvg[y] = float(RawToLux(rawVal));
  Serial.print(luxAvg[y]);
  Serial.println(" - data collected");
  delay(1000);
}
  float average;
  for(int x=0;x<=10;x++){
    average = average + luxAvg[x];
  }
  average = average / 10;
  Serial.println("AVERAGE LUX: ");
  Serial.println(average);
  return average;
}

void loop(){
  float avg = collectAvg();
  Serial.println("COLLECTED AVERAGE: ");
  Serial.print(avg);
  delay(100000);
}
