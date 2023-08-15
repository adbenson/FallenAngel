#ifndef RainbowMode_h
#define RainbowMode_h

#include "Arduino.h"
#include "light_mode.h"

#define MAX            32767

class RainbowMode : public LightMode {
  public:
    RainbowMode(int maxPixels);
   
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
