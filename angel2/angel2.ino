#include "wings.h"
#include "buttons.h"
#include "display.h"
#include "light_mode.h"
#include "chase_mode.h"
#include "fire_mode.h"
#include "glow_mode.h"
#include "rainbow_mode.h"

#include <Adafruit_NeoPixel.h>

// CONSTANTS

#define DELAY 10

// I/O PINS

#define BUTTON_POWER      22 //A
#define BUTTON_UP         23 //B
#define BUTTON_MODE       24 //C
#define BUTTON_DOWN       25 //D

#define PIN_WING_SPEED_OUT    3
#define PIN_WING_DIR_OUT      2

#define ACCESSORY_OUT     30
#define LEFT_WING_OUT     28
#define RIGHT_WING_OUT    26

#define WING_POSITION_IN  A0

#define AUDIO_ENVELOPE_INPUT A1
#define AUDIO_INPUT          A2


//Gloabls
Wings* wings;
Buttons* buttons;

Adafruit_NeoPixel* leftWing;
Adafruit_NeoPixel* rightWing;
Adafruit_NeoPixel* accessory;

GlowMode* wingGlow;
GlowMode* accGlow;

LightMode* wingMode;
LightMode* accessoryMode;

Display* display;

bool lightsOn = true;

void setup() {
  Serial.begin(19200);
  Serial.println("Setup begin");

  wings = new Wings(PIN_WING_SPEED_OUT, PIN_WING_DIR_OUT, WING_POSITION_IN);
  
  buttons = new Buttons(BUTTON_POWER, BUTTON_MODE, BUTTON_UP, BUTTON_DOWN);

  leftWing = new Adafruit_NeoPixel(144, LEFT_WING_OUT, NEO_GRBW + NEO_KHZ800);
  rightWing = new Adafruit_NeoPixel(144, RIGHT_WING_OUT, NEO_GRBW + NEO_KHZ800);
  accessory = new Adafruit_NeoPixel(60, ACCESSORY_OUT, NEO_GRB + NEO_KHZ800);

  wingMode = new RainbowMode(144);
  accessoryMode = new RainbowMode(60);

  wingGlow = new GlowMode(144);
  accGlow = new GlowMode(60);

  display = new Display();

  display->init();

  leftWing->begin();
  rightWing->begin();
  accessory->begin();

  leftWing->setBrightness(255);
  rightWing->setBrightness(255);
  accessory->setBrightness(255);

  wings->stop();

  Serial.println("Setup complete");
}

void moveWings() {
    if (buttons->wasPressed(buttons->DOWN)) {
      wings->down();
    } else if (buttons->wasPressed(buttons->UP)) {
      wings->up();
    }

    wings->step();
}

void blankLights() {
  leftWing->setBrightness(0);
  rightWing->setBrightness(0);
  accessory->setBrightness(0);
  leftWing->show();
  rightWing->show();
  accessory->show();
}

void updateLights(int wingPosition) {
  int brightness = wingPosition / 4;

  leftWing->setBrightness(brightness);
  rightWing->setBrightness(brightness);
  accessory->setBrightness(brightness);

  accessoryMode->step();
  accessoryMode->display(accessory, 0);

  if (buttons->isPressed(buttons->MODE)) {
     wingGlow->step();
     
    wingMode->display(leftWing, 0);
    wingMode->display(rightWing, 0);
  } else {
    wingMode->step();

    wingMode->display(leftWing, 0);
    wingMode->display(rightWing, 0);
  }

  leftWing->show();
  rightWing->show();
  accessory->show();
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

  display->beepBoop();

  delay(DELAY);
}
