#ifndef Buttons_h
#define Buttons_h

#include "Arduino.h"

#define DEBUG false

#define NUM_BUTTONS 4
#define HISTORY 4

class Buttons {
  public:
    Buttons(int power, int mode, int up, int down);

    static const int POWER = 0;
    static const int MODE = 1;
    static const int UP = 2;
    static const int DOWN = 3;

    void update();
    boolean isPressed(int buttonIndex);
    boolean wasPressed(int buttonIndex);

  private:
    boolean buttonHistory[NUM_BUTTONS][HISTORY];
    int buttons[NUM_BUTTONS];

};

#endif
