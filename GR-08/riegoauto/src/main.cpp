#include <Arduino.h>

const int sensor = 12;
int valorsensor;

const int bomba = 14;

void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT_PULLDOWN);

  pinMode(bomba, OUTPUT);
}

void loop()
{
  digitalWrite(bomba, LOW);
  valorsensor = analogRead(sensor);
  if (valorsensor >= 2100)
  {
    digitalWrite(bomba, HIGH);
    delay(500);
    digitalWrite(bomba, LOW);
  }

  // cada 2000 millones de microsegundos (2000 segundos = 33 minutos)
  esp_sleep_enable_timer_wakeup(2000000000);
  esp_deep_sleep_start();
}