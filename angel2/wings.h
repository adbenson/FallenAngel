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

#define POSITION_MIN 140
#define POSITION_MAX 900

class Wings {
  public:
    Wings(int speedPin, int dirPin, int positionPin);
    
    void up();
    void down();
    void stop();

    void step();

    int updatePosition();

  private:
    int speedOut;
    int directionOut;
    int positionIn;
  
    int wingDirection;
    int wingSpeed;
    int position;

    int unmovedCount;

    void move(int direction);
    bool moving();

};

#endif
