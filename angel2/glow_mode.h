#ifndef GlowMode_h
#define GlowMode_h

#include "Arduino.h"
#include "light_mode.h"

class GlowMode : public LightMode {
  public:
    GlowMode(int maxPixels);

    void step();
    void display(Adafruit_NeoPixel* pixels, int meta);

  private:
    int chaseState;
    int maxColor;
};

#endif
