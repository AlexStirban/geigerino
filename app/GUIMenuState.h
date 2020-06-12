#ifndef GUIMENUSTATE_H
#define GUIMENUSTATE_H

#include "GUIState.h"

class GUIMenuState : 
    public GUIState
{
    private:
        byte menuIdx;
    
    public:
        GUIMenuState(Adafruit_SSD1306& display);

        virtual void draw(char* buffer) const;
        virtual byte handleInputEvent (byte type, byte val);
        

};
   

#endif