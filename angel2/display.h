#ifndef Display_h
#define Display_h

#include "Adafruit_LEDBackpack.h"

class Display {
    public:
        Display();
        void init();

        void number(int n);
        void beepBoop();

    private:
        Adafruit_BicolorMatrix* matrix;
        Adafruit_7segment* digits;
        uint8_t* matrixState;
};

#endif