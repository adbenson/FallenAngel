#include "Arduino.h"
#include "glow_mode.h"

GlowMode::GlowMode(int maxPixels) : LightMode(maxPixels) {
  chaseState = 0;

  maxColor = rgbw(255, 255, 255, 255);
};

void GlowMode::step() {
  chaseState++;
  
  if (chaseState >= 6 * 3) {
    chaseState = 0;
  }
}

byte bump(int value) {
  if (value == 255) {
    return 255;
  }

  return constrain(value + 16, 0, 255);  
}

void GlowMode::display(Adafruit_NeoPixel* pixels, int meta) {

  int n = pixels->numPixels();
  
  uint32_t color;
  for (int i=0; i < n; i++) {

    color = pixels->getPixelColor(i);

    if (color < maxColor) {
      byte r = bump(red(color));
      byte g = bump(green(color));
      byte b = bump(blue(color));
      byte w = bump(white(color));

      color = rgbw(r, g, b, w);
    }
    
    pixels->setPixelColor(i, color);
  }
}
