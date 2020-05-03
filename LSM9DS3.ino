#include <Arduino_LSM9DS1.h>

// calibration
const int empty = 0;
const int quarterFilled = 455;
const int halfFilled = 605;
const int threeQuarterFilled = 625;
const int filled = 635;

const int sensorPin = A0;
const int redPin = 22;
const int greenPin = 23;
const int bluePin = 24;

int sensorValue = 0;


void setup() {

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  setLed(255, 255, 255);
  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    setLed(0, 0, 0);
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

      if (sensorValue > filled) {
        Serial.print("100% ");
        setLed(255, 0, 0);
      } else if (sensorValue > threeQuarterFilled) {
        Serial.print("75% ");
        setLed(255, 127, 0);
      } else if (sensorValue > halfFilled) {
        Serial.print("50% ");
        setLed(255, 255, 0);
      } else if (sensorValue > quarterFilled) {
        Serial.print("25% ");
        setLed(0, 255, 0);
      } else {
        Serial.print("0% ");
        setLed(0, 0, 255);
      }
      
      Serial.println(sensorValue);
    } else {
      Serial.println("not standing");
        setLed(255, 0, 255);
    }
    
    delay(100);
  }
  
}

void setLed(int red, int green, int blue) {
  // values are inverted i.e. 255 == off
  analogWrite(redPin, 255 - red);
  analogWrite(greenPin, 255 - green);
  analogWrite(bluePin, 255 - blue);
}
