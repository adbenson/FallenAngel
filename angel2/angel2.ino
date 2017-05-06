#include "wings.h"
#include "buttons.h"
#include "light_mode.h"
#include "chase_mode.h"
#include <Adafruit_NeoPixel.h>

// I/O PINS

#define BUTTON_POWER      22 //A
#define BUTTON_UP         23 //B
#define BUTTON_MODE       24 //C
#define BUTTON_DOWN       25 //D

#define WING_SPEED        3
#define WING_DIR          2

#define HALO_OUT          30
#define LEFT_WING_OUT     28
#define RIGHT_WING_OUT    26


//Gloabls
Wings* wings;
Buttons* buttons;

Adafruit_NeoPixel* leftWing;
Adafruit_NeoPixel* rightWing;

LightMode* mode;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup begin");

  wings = new Wings(WING_SPEED, WING_DIR);
  
  buttons = new Buttons(BUTTON_POWER, BUTTON_MODE, BUTTON_UP, BUTTON_DOWN);

  leftWing = new Adafruit_NeoPixel(144, LEFT_WING_OUT, NEO_GRBW + NEO_KHZ800);
  rightWing = new Adafruit_NeoPixel(144, RIGHT_WING_OUT, NEO_GRBW + NEO_KHZ800);

  mode = new ChaseMode(144);

  leftWing->begin();
  rightWing->begin();

  leftWing->setBrightness(255);
  rightWing->setBrightness(255);

  Serial.println("Setup complete");
}

void moveWings() {
    if (buttons->isPressed(buttons->DOWN)) {
      wings->down();
    } else if (buttons->isPressed(buttons->UP)) {
      wings->up();
    } else {
      wings->stop();
    }
}

void loop() {
  Serial.println("Loop start");

  buttons->update();

  if(buttons->isPressed(buttons->POWER)) Serial.println("power is pressed");
  if(buttons->wasPressed(buttons->POWER)) Serial.println("power was pressed");

  moveWings();

  mode->step();

  mode->display(leftWing);
  mode->display(rightWing);

  leftWing->show();
  rightWing->show();

  delay(100);
}

