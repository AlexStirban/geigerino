#ifndef GUISETTINGSSTATE_H
#define GUISETTINGSSTATE_H

#include <Arduino.h>
#include "GUIState.h"
#include "settingsContainer.h"

class GUISettingsState : 
    public GUIState
{
    private:
        byte settingIdx;
        settingsContainer* config;
    
    public:
        GUISettingsState(Adafruit_SSD1306& display, settingsContainer& config);

        virtual void draw(char* buffer) const;
        virtual byte handleInputEvent (byte type, byte val);
};

#endif