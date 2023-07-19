#define TRIGGER D7
#define ECHO D8
#define SOUND_VELOCITY 0.34  // [mm/us]
#define delay_time 50L
uint32_t ref_time = 0;

float read_distance(uint8_t trigger, uint8_t echo);

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(100);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  ref_time = millis();
}

void loop() {
  if (millis() - ref_time >= delay_time) {
    ref_time = millis();
    Serial.print("mm: ");
    Serial.println(read_distance(TRIGGER, ECHO));
  }
}

float read_distance(uint8_t trigger, uint8_t echo) {
#ifndef SOUND_VELOCITY
#define SOUND_VELOCITY 0.337
#endif
  digitalWrite(trigger, 0);
  delayMicroseconds(2);
  digitalWrite(trigger, 1);
  delayMicroseconds(10);
  digitalWrite(trigger, 0);
  float aux = pulseIn(echo, HIGH);
  return aux * SOUND_VELOCITY / 2;
}