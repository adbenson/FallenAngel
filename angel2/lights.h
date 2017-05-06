#ifndef Lights_h
#define Lights_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

#define DEBUG true

class Lights {
  public:
    Lights(int pin, int count, int type);

    static uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);
    
    static uint32_t hue(byte hue);

  private:
    Adafruit_NeoPixel strip;
    int numPixels;
    int lastPixel;

};

#endif
