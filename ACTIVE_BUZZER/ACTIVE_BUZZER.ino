#define BTN D3
#define BUZZ D8
#define db_time 10L      // tempo descartado para debounce
#define loop_time 50L    // período em (ms) de leitura dos botões
#define buzz_time 1000L  // tempo do buzz ativo
uint32_t loop_ref = 0;   // variávei auxiliar para referência de tempo
bool flag_buzz = 0;      // variável auxiliar para controle do buzzer
bool flag_button = 0;    // variável auxiliar para leitura de borda

// lê a borda de descida de um botão com resistor de pull-up:
// retorna 1-botão pressionado / 0-caso contrário
bool read_btn(uint8_t pin, bool *flag_button, uint8_t debounce_time);

void control_buzz(uint8_t pin, uint8_t time_interval);

void setup() {
  pinMode(BTN, INPUT_PULLUP);  // 1-nível lógico baixo / 0-nível lógico alto
  pinMode(BUZZ, OUTPUT);
  digitalWrite(BUZZ, 0);
  loop_ref = millis();  // atualiza referência de tempo para leitura do botão
}

void loop() {
  if (millis() - loop_ref >= loop_time) {
    loop_ref = millis();
    if (read_btn(BTN, &flag_button, db_time)) {
      flag_buzz = !flag_buzz;
      control_buzz(BUZZ, buzz_time);
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

void control_buzz(uint8_t pin, uint8_t time_interval) {
  unsigned long t_ref = millis();
  pinMode(pin, OUTPUT);
  digitalWrite(pin, 1);
  while (flag_buzz) {
    if (millis() - t_ref >= buzz_time) {
      flag_buzz = 0;
    }
  }
  digitalWrite(pin, 0);
}