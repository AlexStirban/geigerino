#ifndef GUISTATE_H
#define GUISTATE_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class GUIState {
    protected:
        Adafruit_SSD1306* display;

    public:
        GUIState (Adafruit_SSD1306& display) : display(&display) {};

        virtual void draw(char* buffer) const = 0;
        virtual byte handleInputEvent(byte type, byte val) = 0;
};



#endif