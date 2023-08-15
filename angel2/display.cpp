#include "Arduino.h"
#include "display.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

const int N = 8 * 8;

Display::Display() {
    matrix = new Adafruit_BicolorMatrix();
    digits = new Adafruit_7segment();
}

void Display::init() {
    matrixState = new uint8_t[N];

    digits->begin(0x70);
    matrix->begin(0x71);

    digits->print(8888);
    digits->writeDisplay();

    matrix->clear();
    matrix->fillRect(0,0, 3,8, LED_RED);
    matrix->fillRect(3,0, 5,8, LED_YELLOW);
    matrix->fillRect(5,0, 8,8, LED_GREEN);
    matrix->writeDisplay();

    delay(300);
    
    matrix->fillRect(0,0, 8,8, LED_OFF);
    matrix->writeDisplay();
}

void Display::number(int n) {
    digits->print(n);
    digits->writeDisplay();
}

void Display::beepBoop() {
    int p = random(3);
    if (p == 0) {
        int x = random(8);
        int y = random(8);
        int c = random(6) - 2;
        c = max(c, 0);
        matrix->drawPixel(x, y, c);
        matrix->writeDisplay();
    }
}