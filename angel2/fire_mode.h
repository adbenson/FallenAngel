#ifndef FireMode_h
#define FireMode_h

#include "Arduino.h"
#include "light_mode.h"

#define MAX            32767

class FireMode : public LightMode {
  public:
    FireMode(int maxPixels);
   
    void step();
    void display(Adafruit_NeoPixel* pixels, int meta);

  private:
    void pullAdjacent(int i, int pull);

    int* levels;
    int* goals;
                    
    int rise;
    int fall;
    int dropoff;
    int minLevel;
    int choose;
};

#endif
