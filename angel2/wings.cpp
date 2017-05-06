#include "Arduino.h"
#include "wings.h"

Wings::Wings(int speedPin, int dirPin) {
      
  pinMode(speedPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  speedOut = speedPin;
  directionOut = dirPin;

  stop();

  if (DEBUG) {
    Serial.println("wings initialized");
  }
};

void Wings::up() {
  move(WINGS_UP);
}

void Wings::down() {
  move(WINGS_DOWN);
}

void Wings::stop() {
  if (wingDirection >= 0) {
    wingDirection = -1;
    wingSpeed = 0;
    digitalWrite(speedOut, LOW);
  
    if (DEBUG) {
      Serial.println("wings stopped");
    }
  }
}

void Wings::move(int direction) {
  wingDirection = direction;

  wingSpeed += 16;
  wingSpeed = constrain(wingSpeed, 16, 255);

  digitalWrite(directionOut, direction);
  analogWrite(speedOut, wingSpeed);

  if (DEBUG) {
    Serial.print("wing direction: "); Serial.println(direction);
    Serial.print("wing wingSpeed: "); Serial.println(wingSpeed);
  }
}

