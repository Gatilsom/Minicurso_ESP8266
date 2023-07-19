#define BTN D3 
#define R_LED D5
#define G_LED D6
#define B_LED D7
#define delay_time 100L  // long 100 [ms]
#define delay_btn 50L    // long 50 [ms]
#define db_time 5L       // long 10 [ms]

unsigned long ref_time = 0;
unsigned long ref_time_btn = 0;
int16_t pot = 0;
uint8_t aux_led = 0;
bool flag_btn = 0;

// lê a borda de descida de um botão com resistor de pull-up:
// retorna 1-botão pressionado / 0-caso contrário
bool read_btn(uint8_t pin, bool *flag_btn, uint8_t debounce_time);

void setup() {
  analogWriteRange(1023);
  analogWriteFreq(1000);
  Serial.begin(115200);
  while (!Serial) delay(100);
  pinMode(A0, INPUT);
  pinMode(BTN, INPUT_PULLUP);
  pinMode(R_LED, OUTPUT); digitalWrite(R_LED, 0);
  pinMode(G_LED, OUTPUT); digitalWrite(G_LED, 0);
  pinMode(B_LED, OUTPUT); digitalWrite(B_LED, 0);
  ref_time = millis();
  ref_time_btn = millis();
}

void loop() {
  if (millis() - ref_time >= delay_time) {
    ref_time = millis();
    analogRead(A0);  // descarte da primeira leitura
    pot = map(analogRead(A0), 0, 1024, 0, 1023);
    if (pot < 10) pot = 0; // ajuste do pot
    if (aux_led == 0) {
      analogWrite(R_LED, pot);
      analogWrite(G_LED, pot);
      analogWrite(B_LED, pot);
    }
    if (aux_led == 1) analogWrite(R_LED, pot);
    if (aux_led == 2) analogWrite(G_LED, pot);
    if (aux_led == 3) analogWrite(B_LED, pot);
    Serial.print(pot);
    Serial.print("\t");
    Serial.println(aux_led);
  }
  if (millis() - ref_time_btn >= delay_btn) {
    ref_time_btn = millis();
    if (read_btn(BTN, &flag_btn, db_time)) {
      aux_led++;
      if (aux_led > 3) aux_led = 0;
    }
  }
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


