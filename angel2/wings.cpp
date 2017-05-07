#include "Arduino.h"
#include "wings.h"

Wings::Wings(int speedPin, int dirPin, int positionPin) {
      
  pinMode(speedPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  speedOut = speedPin;
  directionOut = dirPin;

  positionIn = positionPin;

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
  if (wingSpeed > 0) {
    wingSpeed -= 32;
    wingSpeed = constrain(wingSpeed, 0, 255);
  
    digitalWrite(speedOut, wingSpeed);
  
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

  int maxSpeed;
  if (direction == WINGS_UP) {
    maxSpeed = map(position, 1024, 640, 32, 255);
  } else {
    maxSpeed = map(position, 0, 256, 32, 255);
  }

  maxSpeed = constrain(maxSpeed, 32, 255);

  wingSpeed = constrain(wingSpeed, 16, maxSpeed);

  digitalWrite(directionOut, direction);
  analogWrite(speedOut, wingSpeed);

  if (DEBUG) {
    Serial.print("wing direction: "); Serial.println(direction);
    Serial.print("wing wingSpeed: "); Serial.println(wingSpeed);
  }
}

