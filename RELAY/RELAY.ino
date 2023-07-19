#define BTN D3
#define RELAY D0
#define db_time 10L     // tempo descartado para debounce
#define loop_time 50L   // período em (ms) de leitura dos botões
uint32_t loop_ref = 0;  // variávei auxiliar para referência de tempo
bool flag_button = 0;   // variável auxiliar para leitura de borda

// lê a borda de descida de um botão com resistor de pull-up:
// retorna 1-botão pressionado / 0-caso contrário
bool read_btn(uint8_t pin, bool *flag_button, uint8_t debounce_time);

void setup() {
  pinMode(BTN, INPUT_PULLUP);  // 1-nível lógico baixo / 0-nível lógico alto
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, 1);
  loop_ref = millis();  // atualiza referência de tempo para leitura do botão
}

void loop() {
  if (millis() - loop_ref >= loop_time) {
    loop_ref = millis();
    if (read_btn(BTN, &flag_button, db_time)) {
      digitalWrite(RELAY, !digitalRead(RELAY));
    }
  }
}

bool read_btn(uint8_t pin, bool *flag_button, uint8_t debounce_time) {
  bool value = 0;
  if (!digitalRead(pin)) {
    if (*flag_button) {
      if (debounce_time > 0) {
        unsigned long t_aux = millis();
        while ((millis() - t_aux >= db_time)) {}
      }
      if (!digitalRead(pin)) value = 1;
      *flag_button = 0;
    }
  } else *flag_button = 1;
  return value;
}