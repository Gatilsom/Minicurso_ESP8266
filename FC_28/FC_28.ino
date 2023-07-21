#define M_TAM 500
#define delay_time 100L
uint16_t fc_value = 0;
float media = 0.0;
unsigned long ref_time = 0;
uint16_t data[M_TAM] = { 0 };

float media_movel(uint16_t value, uint16_t *data, uint16_t tam);

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(100);
  pinMode(A0, INPUT);
  ref_time = millis();
}

void loop() {
  if (millis() - ref_time >= delay_time) {
    ref_time = millis();
    analogRead(A0);
    fc_value = analogRead(A0);
    media = media_movel(fc_value, data, M_TAM);
    Serial.print("1024:");
    Serial.print(1024);
    Serial.print(",0000:");
    Serial.print(0);
    Serial.print(",fc28:");
    Serial.print(fc_value);
    Serial.print(",media:");
    Serial.println(media);
  }
}

float media_movel(uint16_t value, uint16_t *data, uint16_t tam) {
  for (int i = 0; i < M_TAM - 1; i++) data[i] = data[i + 1];
  data[M_TAM - 1] = value;
  float media = 0.0;
  analogRead(A0);
  for (int i = 0; i < M_TAM; i++) media += analogRead(A0);
  return media / M_TAM;
}