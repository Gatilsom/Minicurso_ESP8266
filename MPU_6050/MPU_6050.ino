#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#define delay_time 10L
unsigned long ref_time = 0;
Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(100);
  while (!mpu.begin()) {
    Serial.println(F("Erro de inicializacao ..."));
    delay(delay_time);
  }
  // configurações do MPU
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(delay_time * 10);
  ref_time = millis();
}

void loop() {
  if (millis() - ref_time >= delay_time) {
    ref_time = millis();
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    Serial.print("acel_x:");         // Serial.print("omega_x:");
    Serial.print(a.acceleration.x);  // Serial.print(g.gyro.x);
    Serial.print(",");
    Serial.print("acel_y:");         // Serial.print("omega_y:");
    Serial.print(a.acceleration.y);  // Serial.print(g.gyro.y);
    Serial.print(",");
    Serial.print("acel_z:");           // Serial.print("omega_z:");
    Serial.println(a.acceleration.z);  // Serial.print(g.gyro.z);
  }
}