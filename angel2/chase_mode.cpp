#include "Arduino.h"
#include "chase_mode.h"

ChaseMode::ChaseMode(int maxPixels) : LightMode(maxPixels) {
  chaseState = 0;
};

void ChaseMode::step() {
  chaseState++;
  
  if (chaseState >= 6 * 3) {
    chaseState = 0;
  }
}

void ChaseMode::display(Adafruit_NeoPixel* pixels) {

  int n = pixels->numPixels();
  
  uint32_t color;
  for (int i=0; i < n; i++) {
    int offset = (i + (chaseState/3)) % 6;
    switch (offset) {
    case 0: 
      color = rgb(127, 0, 0); 
      break;
    case 1: 
      color = rgb(127, 63, 0); 
      break;
    case 2: 
      color = rgb(127, 127, 0); 
      break;
    case 3: 
      color = rgb(0, 127, 0); 
      break;
    case 4: 
      color = rgb(0, 0, 255); 
      break;
    case 5: 
      color = rgb(63, 0, 255); 
      break;
    }
    
    pixels->setPixelColor(i, color);
  }
}
