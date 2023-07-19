#define BTN D3 
#define MUX_S0 D0
#define MUX_S1 D1
#define MUX_S2 D2
#define MUX_S3 D4
#define delay_time 100L  // long 100 [ms]
#define delay_btn 50L    // long 50 [ms]
#define db_time 5L       // long 10 [ms] tempo descartado para debounce

unsigned long ref_time_joy = 0;
unsigned long ref_time_btn = 0;
int16_t x_joy = 0;
int16_t y_joy = 0;
int16_t c_joy = 0;
bool flag_btn = 0;  // variável auxiliar para leitura de borda

uint16_t calc_angle(int16_t x_joy, int16_t y_joy);

// lê a borda de descida de um botão com resistor de pull-up:
// retorna 1-botão pressionado / 0-caso contrário
bool read_btn(uint8_t pin, bool *flag_btn, uint8_t debounce_time);

void setup() {
  analogWriteRange(1023);
  analogWriteFreq(1000);
  Serial.begin(115200);
  while (!Serial) delay(100);
  pinMode(BTN, INPUT_PULLUP);
  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);
  pinMode(MUX_S3, OUTPUT);
  digitalWrite(MUX_S0, 0);
  digitalWrite(MUX_S1, 0);
  digitalWrite(MUX_S2, 0);
  digitalWrite(MUX_S3, 0);
  ref_time_joy = millis();
  ref_time_btn = millis();
}

void loop() {
  if (millis() - ref_time_joy >= delay_time) {
    ref_time_joy = millis();
    digitalWrite(MUX_S0, 0);
    digitalWrite(MUX_S1, 0);
    analogRead(A0);  // descarte da primeira leitura
    x_joy = map(analogRead(A0), 0, 1024, -1, 1);
    digitalWrite(MUX_S0, 1);
    digitalWrite(MUX_S1, 0);
    analogRead(A0);  // descarte da primeira leitura
    y_joy = map(analogRead(A0), 1024, 0, -1, 1);
    Serial.print(x_joy);
    Serial.print("\t");
    Serial.print(y_joy);
    Serial.print("\t");
    Serial.print(calc_angle(x_joy, y_joy));
    Serial.print("º");
    Serial.print("\t");
    Serial.println(c_joy);
  }

  if (millis() - ref_time_btn >= delay_btn) {
    ref_time_btn = millis();
    if (read_btn(BTN, &flag_btn, db_time)) {
      c_joy++;
    }
  }
}

uint16_t calc_angle(int16_t x_joy, int16_t y_joy) {
  if (x_joy == 1 && y_joy == 0) return 0;
  if (x_joy == 1 && y_joy == 1) return 45;
  if (x_joy == 0 && y_joy == 1) return 90;
  if (x_joy == -1 && y_joy == 1) return 135;
  if (x_joy == -1 && y_joy == 0) return 180;
  if (x_joy == -1 && y_joy == -1) return 225;
  if (x_joy == 0 && y_joy == -1) return 270;
  if (x_joy == 1 && y_joy == -1) return 315;
  return 999;
}

bool read_btn(uint8_t pin, bool *flag_btn, uint8_t debounce_time) {
  bool value = 0;
  if (!digitalRead(pin)) {
    if (*flag_btn) {
      if (debounce_time > 0) {
        unsigned long t_aux = millis();
        while ((millis() - t_aux >= db_time)) {}
      }
      if (!digitalRead(pin)) value = 1;
      *flag_btn = 0;
    }
  } else *flag_btn = 1;
  return value;
}