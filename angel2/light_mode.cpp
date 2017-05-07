#include "Arduino.h"
#include "light_mode.h"

LightMode::LightMode(int maxPixels) {
  numPixels = maxPixels;
  lastPixel = maxPixels - 1;
}

uint32_t LightMode::rgb(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

uint32_t LightMode::rgbw(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t LightMode::hue(byte hue) {
  hue = 255 - (hue % 255);
  
  if (hue < 85) {
    return rgb(255 - hue * 3, 0, hue * 3);
  } else if (hue < 170) {
    hue -= 85;
    return rgb(0, hue * 3, 255 - hue * 3);
  } else {
    hue -= 170;
    return rgb(hue * 3, 255 - hue * 3, 0);
  }
}

uint32_t LightMode::red(uint32_t color) {
  return (color >> 16) & 255;
}

uint32_t LightMode::green(uint32_t color) {
  return (color >> 8) & 255;
}

uint32_t LightMode::blue(uint32_t color) {
  return color & 255;
}

uint32_t LightMode::white(uint32_t color) {
  return (color >> 24) & 255;
}





