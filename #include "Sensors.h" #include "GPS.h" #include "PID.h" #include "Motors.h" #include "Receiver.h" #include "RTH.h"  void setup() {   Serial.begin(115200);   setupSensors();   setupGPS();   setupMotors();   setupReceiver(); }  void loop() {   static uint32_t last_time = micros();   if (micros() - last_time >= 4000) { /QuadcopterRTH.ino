```
#include "Sensors.h"
#include "GPS.h"
#include "PID.h"
#include "Motors.h"
#include "Receiver.h"
#include "RTH.h"

void setup() {
  Serial.begin(115200);
  setupSensors();
  setupGPS();
  setupMotors();
  setupReceiver();
}

void loop() {
  static uint32_t last_time = micros();
  if (micros() - last_time >= 4000) { // 250 Hz loop
    readSensors();
    checkFailsafe();
    handleRTH();
    calculatePID();
    updateMotors();
    last_time = micros();
  }
}
```
