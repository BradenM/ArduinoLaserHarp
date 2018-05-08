 #include <Arduino.h>

int sensorPin = A0;
float rawRange = 1024; // 3.3v
float logRange = 5.0; // 3.3v = 10^5 lux

void setup()
{
  analogReference(EXTERNAL); //
  Serial.begin(9600);
}

float RawToLux(int raw)
{
  float logLux = raw * logRange / rawRange;
  return pow(10, logLux);
}

void loop()
{
  int rawValue = analogRead(sensorPin);

  Serial.print("Raw = ");
  Serial.print(rawValue);
  Serial.print(" - Lux = ");
  Serial.println(RawToLux(rawValue));
  delay(1000);
}
