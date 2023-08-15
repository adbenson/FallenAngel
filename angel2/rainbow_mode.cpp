#include "Arduino.h"
#include "rainbow_mode.h"

RainbowMode::RainbowMode(int maxPixels) : LightMode(maxPixels) {

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

void RainbowMode::step() {

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

void RainbowMode::display(Adafruit_NeoPixel* pixels, int wing) {
  for(int i = 0; i < numPixels; i++){
    int level = levels[i];

    float factor = (float)level / MAX;
    int r = 255 * factor;
    int g = 255 * factor * factor;
    int b = 50 * factor * factor;
    int w = (factor < 0.25 && random(0, 20) == 0) ? 255 : 0;
    
    uint32_t color = hue(factor * 255);
    color = setWhite(color, w);

    pixels->setPixelColor(i, color);
  }
}

void RainbowMode::pullAdjacent(int i, int pull) {
  i = ((i<0)? lastPixel : i);
  i = (i>lastPixel)? 0 : i;

  int level = pull - dropoff;
  if (goals[i] < level) {
    goals[i] = level;
    pullAdjacent(i-1, level);
    pullAdjacent(i+1, level); 
  }
}
