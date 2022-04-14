#include <Arduino.h>
#include <imu.h>

//#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

void setup() {
    Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately
    initIMUs();
}

void loop() {
  // if programming failed, don't try to do anything
  if (!dmpReady || !dmpReady2) return;

  EulerAngles a = getRelativeAngles();

  Serial.print("pitch: ");
  Serial.print(a.pitch);
  Serial.print(" roll: ");
  Serial.print(a.roll);
  Serial.print(" yaw: ");
  Serial.println(a.yaw);
}
