#ifndef ChaseMode_h
#define ChaseMode_h

#include "Arduino.h"
#include "light_mode.h"

class ChaseMode : public LightMode {
  public:
    ChaseMode(int maxPixels);

    void step();
    void display(Adafruit_NeoPixel* pixels, int meta);

  private:
    int chaseState;
};

#endif
