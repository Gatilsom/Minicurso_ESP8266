#include <Wire.h>
#include <Adafruit_BMP280.h>
#define BMP_SCK (D1)   // pino SCL
#define BMP_MOSI (D2)  // pino SDA
#define ADDR (0x76)
#define delay_time (2000)
unsigned long ref_time = 0;
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(100);
  while (!bmp.begin(ADDR)) {
    Serial.println(F("Erro de inicializacao ..."));
    delay(delay_time);
  }
  // configuração do BMP 280
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* modo de operação */
                  Adafruit_BMP280::SAMPLING_X2,     /* oversampling de temperatura */
                  Adafruit_BMP280::SAMPLING_X16,    /* oversampling de pressão*/
                  Adafruit_BMP280::FILTER_X16,      /* filtragem */
                  Adafruit_BMP280::STANDBY_MS_500); /* tempo de espera */

  ref_time = millis();
}

void loop() {
  if (millis() - ref_time >= delay_time) {
    ref_time = millis();  // atualiza referência de tempo
    Serial.print(F("temperatura = "));
    Serial.print(bmp.readTemperature());
    Serial.println(F(" ºC"));
    Serial.print(F("pressão = "));
    Serial.print(bmp.readPressure());
    Serial.println(F(" Pa"));
    Serial.print(F("altitude aproximada = "));
    Serial.print(bmp.readAltitude(1013.25), 0);
    Serial.println(F(" m"));
    Serial.println();
  }
}