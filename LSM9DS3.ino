#include <Arduino_LSM9DS1.h>

void setup() {

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  
}

void loop() {
  
  float x, y, z;

  if (IMU.accelerationAvailable()) {

    IMU.readAcceleration(x, y, z);

    if (x <= -0.95 && x >= -1.05) {
      Serial.println("standing");
    } else {
      Serial.println("not standing");
    }

  }
  
}
