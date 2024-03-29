#include "Arduino.h"
#include "wings.h"
#include "display.h"

extern Display* display;

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
    if (DEBUG && moving()) {
      Serial.println("wings stopped");
    }
//    wingSpeed -= 32;
//    wingSpeed = constrain(wingSpeed, 0, 255);

    wingDirection = WINGS_STOP;
    wingSpeed = 0;
    unmovedCount = 0;
    digitalWrite(speedOut, 0);
  
//    if (DEBUG) {
//      Serial.println("wings stopped");
//    }
}

int Wings::updatePosition() {
  int reading = analogRead(positionIn);
  display->number(reading);

  int mapped = map(reading, POSITION_MIN, POSITION_MAX, 0, 1023);
  int newPosition = constrain(mapped, 0, 1023);

  if (moving() && abs(newPosition - position) <= 1) {
    unmovedCount++;
  } else {
    unmovedCount = 0;
  }

  position = newPosition;
  
  return position;
}

bool Wings::moving() {
  return (wingDirection != WINGS_STOP) || (wingSpeed > 0);
}

void Wings::move(int direction) {
  if (DEBUG) {
    Serial.println("Wing direction requested");
  }

  if (moving()) {
    if (wingDirection != direction) {
      stop();
    }
  } else {
    wingDirection = direction;
    if (DEBUG) {
      Serial.println("Wing direction set");
    }
  }
}

void Wings::step() {
  if (moving()) {
    if (unmovedCount > 10) {
      if (DEBUG) {
        Serial.println("Wings stalled");
        Serial.print("Wing speed: "); Serial.println(wingSpeed);
      }

      stop();
      return;
    }

    // Serial.println(position);
  
    if ((wingDirection == WINGS_UP && position > 768) || wingDirection == WINGS_DOWN && position < 256)  {
      wingSpeed -= 32;
    } else {
      wingSpeed += 32;
    }

    // int maxSpeed;
    // if (wingDirection == WINGS_UP) {
    //   maxSpeed = map(position, 1023, 767, 32, 255);
    // } else {
    //   maxSpeed = map(position, 0, 255, 32, 255);
    // }

    // maxSpeed = constrain(maxSpeed, 32, 255);
  
    wingSpeed = constrain(wingSpeed, 32, 255);
  
    digitalWrite(directionOut, wingDirection);
    analogWrite(speedOut, wingSpeed);
    
  }

}

