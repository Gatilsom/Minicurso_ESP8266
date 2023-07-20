
#define AMOSTRAS 10
#define BETA_COEF 3950
#define NOMINAL_RES 5165
#define NOMINAL_NTC 10000
#define NTC_PIN A0

#define delay_time (100)
unsigned long ref_time = 0;

float read_NTC(uint8_t pin, uint8_t n_samples, float NTC_nominal, float R_serie, float beta);

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(100);
  pinMode(NTC_PIN, INPUT);
  ref_time = millis();
}

void loop() {
  if (millis() - ref_time >= delay_time) {
    ref_time = millis();
    Serial.print("temperatura: ");
    Serial.println(read_NTC(NTC_PIN, AMOSTRAS, NOMINAL_NTC, NOMINAL_RES, BETA_COEF));
  }
}

float read_NTC(uint8_t pin, uint8_t n_samples, float NTC_nominal, float R_serie, float beta){
  float average = 0.0;
  analogRead(pin);
  for (uint8_t i = 0; i < n_samples; i++) {
    average += analogRead(pin);
  }
  average = map(average, 0, 1024, 0, 1023) / n_samples;
  float resistance = R_serie / (1023.0 / average - 1.0);
  float steinhart = resistance / NTC_nominal;
  steinhart = logf(steinhart);         // ln(R/Ro)
  steinhart /= beta;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (25.0 + 273.15);  // + (1/To)
  steinhart = 1.0 / steinhart;         // Invert
  steinhart -= 273.15;                 // convert to C
  return steinhart;
}