#include "Arduino.h"
#include "buttons.h"

Buttons::Buttons(int power, int mode, int up, int down) {
  for(int button = 0; button < NUM_BUTTONS; button++) {
    for (int time = 0; time < HISTORY; time++) {
      buttonHistory[button][time] = false;
    }
  }

  buttons[POWER] = power;
  buttons[MODE] = mode;
  buttons[UP] = up;
  buttons[DOWN] = down;

  if (DEBUG) {
    Serial.println("butons initialized");
  }
};

void Buttons::update() {
  for(int i = 0; i < NUM_BUTTONS; i++) {
    boolean current = digitalRead(buttons[i]);

    buttonHistory[i][3] = buttonHistory[i][2];  
    buttonHistory[i][2] = buttonHistory[i][1];
    buttonHistory[i][1] = buttonHistory[i][0];
    buttonHistory[i][0] = current;

    if (DEBUG) {
      Serial.print("button "); Serial.print(i); Serial.println(" : "); Serial.println(current);    
    }
  }
}

boolean Buttons::isPressed(int button) {
  int pressed = 0;
  
  for (int time = 0; time < HISTORY; time++) {
    if (buttonHistory[button][time]) {
      pressed++;
    } 
  }

  return pressed >= 2;
}

boolean Buttons::wasPressed(int button) {
  //Only return true once for each press, and only after it has been pressed for at least one cycle.
  boolean pressed = buttonHistory[button][0] && !buttonHistory[button][1];// && !buttonHistory[button][2]; 

  return pressed;
}

