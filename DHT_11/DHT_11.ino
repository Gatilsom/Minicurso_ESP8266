#include "DHT.h"
#define DHTPIN D5  // pino de dados
#define DHTTYPE DHT11
#define delay_time 2000L
DHT dht(DHTPIN, DHTTYPE);
uint32_t ref_time = 0;
float h = 0.0, t = 0.0;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(100);
  dht.begin();
  ref_time = millis();
}

void loop() {
  if (millis() - ref_time >= delay_time) {
    ref_time = millis();
    h = dht.readHumidity();
    t = dht.readTemperature();  // temperatura em Celsius
    // checagem de leitura válida
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Leitura invalida ..."));
      return;
    }
    Serial.print(F("temperatura: "));
    Serial.print(t);
    Serial.print(F(" ºC\tumidade: "));
    Serial.print(h);
    Serial.println(F(" %"));
  }
}