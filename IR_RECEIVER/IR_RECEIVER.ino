#define DECODE_NEC  // Includes Apple and Onkyo
#define IR_RECEIVE D5
#define delay_time 100L
uint32_t ref_time = 0;

#include <IRremote.hpp>

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(100);
  IrReceiver.begin(IR_RECEIVE, ENABLE_LED_FEEDBACK);
  ref_time = millis();
}

void loop() {
  if (millis() - ref_time >= delay_time) {
    ref_time = millis();
    if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.command);
      IrReceiver.resume();  // Enable receiving of the next value
    }
  }
}