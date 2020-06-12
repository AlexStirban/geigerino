#include "GUIMenuState.h"

#include "stringsTable.h"
#include "events.h"
#include "inputs.h"

GUIMenuState::GUIMenuState(Adafruit_SSD1306& display) :
    GUIState(display),
    menuIdx(0)
{

}


void GUIMenuState::draw(char* buffer) const {
    display->setTextColor(WHITE);
    display->drawRect(0, 0, 128, 16, WHITE);

    // HEADER
    display->setCursor(4, 4);
    display->setTextColor(WHITE);
    display->print(F("Menu"));

    // PRINT SETTINGS
    display->setCursor(0, 20);


    for (byte i = 0; i < menu_str_table_len; i++) {
        if (menuIdx == i) {
            display->setTextColor(BLACK, WHITE);
        }
        else {
            display->setTextColor(WHITE);
        }
        strcpy_P(buffer, (char *)pgm_read_word(&(menu_str_table[i])));
        display->print(buffer);
        display->print(F("\n"));

    } 
}


byte GUIMenuState::handleInputEvent(byte type, byte val) {
        switch(val) {
        case buttons::LEFT:
            menuIdx = (menuIdx + 1) % menu_str_table_len ;
            break;
            
        case buttons::RIGHT:
            switch (menuIdx)
            {
            case 0:
                return eventReturn::LAUNCH_COUNTING;
                break;
            
            case 1:
                return eventReturn::LAUNCH_SETTINGS;
                break;

            case 2:
                return eventReturn::LAUNCH_HOMESCREEN;
                break;

            default:
                break;
            }

        default:
            break;
    }

    return eventReturn::NO_ACTION;
}