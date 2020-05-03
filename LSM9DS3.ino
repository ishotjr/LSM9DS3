#include <Arduino_LSM9DS1.h>

// calibration
const int empty = 0;
const int quarterFilled = 455;
const int halfFilled = 605;
const int threeQuarterFilled = 625;
const int filled = 635;

const float standingTolerance = 0.05;

const int sensorPin = A0;
const int redPin = 22;
const int greenPin = 23;
const int bluePin = 24;

const int samples = 10;
int sensorValues[samples] = {0};
int sampleIndex = 0;
int sensorValueTotal = 0;
int sensorValueAverage = 0;


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

    if (x <= (-1 + standingTolerance) && x >= (-1 - standingTolerance)) {
      Serial.print("standing: ");
        
      // remove oldest value from total
      sensorValueTotal -= sensorValues[sampleIndex];
      
      sensorValues[sampleIndex] = analogRead(sensorPin);
      sensorValueTotal += sensorValues[sampleIndex];
      sensorValueAverage = sensorValueTotal / samples;
      
      if (sensorValueAverage > filled) {
        Serial.print("100% ");
        setLed(255, 0, 0);
      } else if (sensorValueAverage > threeQuarterFilled) {
        Serial.print("75% ");
        setLed(255, 127, 0);
      } else if (sensorValueAverage > halfFilled) {
        Serial.print("50% ");
        setLed(255, 255, 0);
      } else if (sensorValueAverage > quarterFilled) {
        Serial.print("25% ");
        setLed(0, 255, 0);
      } else {
        Serial.print("0% ");
        setLed(0, 0, 255);
      }

      // wrap index if needed
      sampleIndex++;
      if (sampleIndex == samples)
      {
        sampleIndex = 0;
      }
  
      Serial.println(sensorValueAverage);
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
