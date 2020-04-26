#include <Arduino_LSM9DS1.h>

int sensorPin = A0;
int sensorValue = 0;

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
      Serial.print("standing: ");
      sensorValue = analogRead(sensorPin);
      Serial.println(sensorValue);
    } else {
      Serial.println("not standing");
    }
    
    delay(1);
  }
  
}
