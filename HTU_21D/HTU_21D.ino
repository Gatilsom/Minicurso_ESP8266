#include <Wire.h>
#include "Adafruit_HTU21DF.h"
#define delay_time 2000L
unsigned long ref_time = 0;
Adafruit_HTU21DF htu = Adafruit_HTU21DF();

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(100);
  while (!htu.begin()) {
    Serial.println(F("Erro de inicializacao ..."));
    delay(delay_time);
  }
  ref_time = millis();
}

void loop() {
  if (millis() - ref_time >= delay_time) {
    ref_time = millis();
    Serial.print(F("temperatura = "));
    Serial.print(htu.readTemperature());
    Serial.println(F(" ºC"));
    Serial.print(F("umidade = "));
    Serial.print(htu.readHumidity());
    Serial.println(F(" %"));
    Serial.println();
  }
}