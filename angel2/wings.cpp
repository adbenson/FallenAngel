#include "Arduino.h"
#include "wings.h"

Wings::Wings(int speedPin, int dirPin, int positionPin) {
      
  pinMode(speedPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  speedOut = speedPin;
  directionOut = dirPin;

  positionIn = positionPin;

  maxSpeed = 255;

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

int Wings::updatePosition() {
  int reading = analogRead(positionIn);
  int mapped = map(reading, POSITION_MIN, POSITION_MAX, 0, 1023);
  position = constrain(mapped, 0, 1023);
  
  return position;
}

void Wings::move(int direction) {
  wingDirection = direction;

  wingSpeed += 32;
  wingSpeed = constrain(wingSpeed, 16, maxSpeed);

  digitalWrite(directionOut, direction);
  analogWrite(speedOut, wingSpeed);

  if (DEBUG) {
    Serial.print("wing direction: "); Serial.println(direction);
    Serial.print("wing wingSpeed: "); Serial.println(wingSpeed);
  }
}

