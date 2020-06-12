#ifndef GUICOUTINGSTATE_H
#define GUICOUTINGSTATE_H

#include "GUIState.h"

class GUICountingState :
    public GUIState
{
    private:
        byte scrollingIdx;
        byte countingIdx;
        unsigned int  ncounts;
        unsigned int  n;
        unsigned long deltaCount;
        unsigned long curr;
        unsigned long prev;
        unsigned int deltaTime;
        unsigned long prevMillis;
        bool isCounting;


    public:
        GUICountingState(Adafruit_SSD1306& display);

        void update(unsigned long& currentCount); 
        virtual void draw(char* buffer) const;
        virtual byte handleInputEvent (byte type, byte val);


};

#endif