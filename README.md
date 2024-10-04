```
// Include the PPM library
#include "ppm.h"

// Include the Servo library (used to control ESCs)
#include <Servo.h>

// Create servo objects to control ESCs (which control motors)
Servo esc_1;
Servo esc_2;
Servo esc_3;
Servo esc_4;

// PPM channel layout (update for your situation)
#define THROTTLE        3
#define ROLL            1
#define PITCH           2
#define YAW             4

// Neutral values for motor control
const int neutralThrottle = 1000; // Min throttle to arm ESCs (usually between 1000 and 2000)
const int neutralYaw = 1500;

// Loop interval time (time in milliseconds between updates)
const long interval = 50;
unsigned long previousMillis = 0; // Stores last time loop was updated

void setup() {
  // Start the serial port to display data 
  Serial.begin(115200);

  // Start the PPM function on PIN A0
  ppm.begin(3, false);

  // Attach ESCs to pins
  esc_1.attach(5);  // Motor 1 (Front-left)
  esc_2.attach(6);  // Motor 2 (Front-right)
  esc_3.attach(9);  // Motor 3 (Back-right)
  esc_4.attach(10);  // Motor 4 (Back-left)

  // Initialize motors with neutral throttle (safety)
  esc_1.writeMicroseconds(neutralThrottle);
  esc_2.writeMicroseconds(neutralThrottle);
  esc_3.writeMicroseconds(neutralThrottle);
  esc_4.writeMicroseconds(neutralThrottle);

  delay(1000); // Allow some time for ESC calibration
}

void loop() {
  // Interval at which the PPM is updated
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Read the values from the PPM receiver
    short throttle  = ppm.read_channel(THROTTLE);
    short roll      = ppm.read_channel(ROLL) - 1500;  // Centering roll
    short pitch     = ppm.read_channel(PITCH) - 1500; // Centering pitch
    short yaw       = ppm.read_channel(YAW) - 1500;   // Centering yaw

    // Adjust the throttle, roll, pitch, and yaw for drone control
    // Mix inputs to control each motor's speed

    // Front-left motor (M1)
    int motor_1_speed = throttle + pitch + roll - yaw;
    // Front-right motor (M2)
    int motor_2_speed = throttle + pitch - roll + yaw;
    // Back-right motor (M3)
    int motor_3_speed = throttle - pitch - roll - yaw;
    // Back-left motor (M4)
    int motor_4_speed = throttle - pitch + roll + yaw;

    // Constrain motor values to be between 1000 and 2000 microseconds
    motor_1_speed = constrain(motor_1_speed, 1000, 2000);
    motor_2_speed = constrain(motor_2_speed, 1000, 2000);
    motor_3_speed = constrain(motor_3_speed, 1000, 2000);
    motor_4_speed = constrain(motor_4_speed, 1000, 2000);

    // Write the constrained values to the ESCs
    esc_1.writeMicroseconds(motor_1_speed);
    esc_2.writeMicroseconds(motor_2_speed);
    esc_3.writeMicroseconds(motor_3_speed);
    esc_4.writeMicroseconds(motor_4_speed);

    // Print the values to the Serial Monitor for debugging
    Serial.print("Throttle: ");
    Serial.print(throttle);
    Serial.print("\tRoll: ");
    Serial.print(roll + 1500);  // Print actual value from PPM
    Serial.print("\tPitch: ");
    Serial.print(pitch + 1500); // Print actual value from PPM
    Serial.print("\tYaw: ");
    Serial.print(yaw + 1500);   // Print actual value from PPM
    Serial.print("\tM1: ");
    Serial.print(motor_1_speed);
    Serial.print("\tM2: ");
    Serial.print(motor_2_speed);
    Serial.print("\tM3: ");
    Serial.print(motor_3_speed);
    Serial.print("\tM4: ");
    Serial.println(motor_4_speed);
  }
}
