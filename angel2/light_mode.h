#ifndef LightMode_h
#define LightMode_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class LightMode {
  public:
    LightMode(int maxPixels);
    
    virtual void step() = 0;

    virtual void display(Adafruit_NeoPixel* strip, int meta) = 0;

    static uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);
    static uint32_t rgbw(uint8_t r, uint8_t g, uint8_t b, uint8_t w);    
    static uint32_t hue(byte hue);

  protected:
    int numPixels;
    int lastPixel;
};

#endif
