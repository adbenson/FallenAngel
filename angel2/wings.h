#ifndef Wings_h
#define Wings_h

#include "Arduino.h"

#define DEBUG true

// PINS
#define WING_SPEED        3
#define WING_DIR          2

// CONSTANTS
#define WINGS_STOP  -1
#define WINGS_UP    LOW
#define WINGS_DOWN  HIGH

class Wings {
  public:
    Wings(int speedPin, int dirPin);
    
    void up();
    void down();
    void stop();

  private:
    int speedOut;
    int directionOut;
  
    int wingDirection;
    int wingSpeed;

    void move(int direction);

};

#endif
