#include "Arduino.h"
#include "fire_mode.h"

FireMode::FireMode(int maxPixels) : LightMode(maxPixels) {

  levels = new int[maxPixels];
  goals = new int[maxPixels];

  for (int i = 0; i < numPixels; i++) {
    levels[i] = 0; 
    goals[i] = MAX;
  }

  rise = 0.05 * MAX;
  fall = 0.02 * MAX;
  dropoff = 0.25 * MAX;
  minLevel = 0.15 * MAX;
  choose = 120;

};

void FireMode::step() {

  for(int i = 0; i < numPixels; i++){
    int level = levels[i];

    if (level < goals[i]) {
      //watch out for overflow!
      long newLevel = (long)level + rise;
      level = min(newLevel, MAX);
    }
    else {
      goals[i] = 0;
      level = max(level - fall, minLevel);
    }

    int r = random(choose);
    if (r == 0) {
      goals[i] = MAX;        
      pullAdjacent(i-1, MAX); 
      pullAdjacent(i+1, MAX); 
    }

    levels[i] = level;    

    float factor = (float)level / MAX;
    uint32_t color = rgb(235 * factor, 255 * factor * factor, 50 * factor * factor);
  }
}

void FireMode::display(Adafruit_NeoPixel* pixels, int wing) {
  for(int i = 0; i < numPixels; i++){
    int level = levels[i];

    float factor = (float)level / MAX;
    int r = 235 * factor;
    int g = 255 * factor * factor;
    int b = 50 * factor * factor;
    
    uint32_t color; 
    
    if (wing == 1) {
      color = rgbw(r, g, b, r);
    } else {
      color = rgbw(b, g, r, r);
    }
    
    pixels->setPixelColor(i, color);
  }
}

void FireMode::pullAdjacent(int i, int pull) {
  i = ((i<0)? lastPixel : i);
  i = (i>lastPixel)? 0 : i;

  int level = pull - dropoff;
  if (goals[i] < level) {
    goals[i] = level;
    pullAdjacent(i-1, level);
    pullAdjacent(i+1, level); 
  }
}
