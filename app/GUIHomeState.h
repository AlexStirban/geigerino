#ifndef GUIHOMESTATE_H
#define GUIHOMESTATE_H

#include "GUIState.h"
#include "geigerCounter.h"

class GUIHomeState:
    public GUIState
{
    private:
        byte unitIdx;
        geigerCounter* counter;

        

    public:
        GUIHomeState (Adafruit_SSD1306& display, geigerCounter& counter);
        
        virtual void draw(char* buffer) const;
        virtual byte handleInputEvent (byte type, byte val);
};


#endif
