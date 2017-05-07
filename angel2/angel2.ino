#include "wings.h"
#include "buttons.h"
#include "light_mode.h"
#include "chase_mode.h"
#include <Adafruit_NeoPixel.h>

// CONSTANTS

#define DELAY 10

// I/O PINS

#define BUTTON_POWER      22 //A
#define BUTTON_UP         23 //B
#define BUTTON_MODE       24 //C
#define BUTTON_DOWN       25 //D

#define WING_SPEED_OUT    3
#define WING_DIR_OUT      2

#define HALO_OUT          30
#define LEFT_WING_OUT     28
#define RIGHT_WING_OUT    26

#define WING_POSITION_IN  A0

#define AUDIO_ENVELOPE_IN A1
#define AUDIO_IN          A2


//Gloabls
Wings* wings;
Buttons* buttons;

Adafruit_NeoPixel* leftWing;
Adafruit_NeoPixel* rightWing;

LightMode* mode;

bool lightsOn = true;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup begin");

  wings = new Wings(WING_SPEED_OUT, WING_DIR_OUT, WING_POSITION_IN);
  
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

void blankLights() {
  leftWing->setBrightness(0);
  rightWing->setBrightness(0);
  leftWing->show();
  rightWing->show();
}

void updateLights(int wingPosition) {
  int brightness = wingPosition / 4;
    
  mode->step();

  mode->display(leftWing);
  mode->display(rightWing);

  leftWing->setBrightness(brightness);
  rightWing->setBrightness(brightness);

  leftWing->show();
  rightWing->show();
}

void loop() {
  // Serial.println("Loop start");

  buttons->update();

  int wingPosition = wings->updatePosition();
  moveWings();

  if (buttons->wasPressed(buttons->POWER)) {
    lightsOn = !lightsOn;

    if (!lightsOn) {
        blankLights();
    }
  }

  if (lightsOn) {
    updateLights(wingPosition);
  }

  delay(DELAY);
}

