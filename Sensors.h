```
#ifndef SENSORS_H
#define SENSORS_H

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Adafruit_MS5611.h>

extern MPU6050 mpu;
extern Adafruit_MS5611 ms5611;
extern float roll, pitch, current_altitude;

void setupSensors();
void readSensors();

#endif
```
