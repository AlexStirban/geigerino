#include "GUIHomeState.h"
#include "events.h"
#include "units.h"
#include "inputs.h"
#include "stringsTable.h"

GUIHomeState::GUIHomeState(Adafruit_SSD1306& display, geigerCounter& counter) :
    GUIState(display),
    counter(&counter),
    unitIdx(0)
{
    
}


void GUIHomeState::draw(char* buffer) const {
    display->setTextColor(WHITE);
    display->setCursor(0, 0);
    display->setTextSize(3);

    switch (unitIdx) {
        case Units::UCPM:
            display->print(counter->CPM);
            break;

        case Units::UCPS:
            display->print(counter->CPS);
            break;

        case Units::UuSv:
            display->print(counter->uSvPerHr);
            break;

        case Units::UmRt:
            display->print(counter->mRtPerHr);
            break;

        default:
            break;
    }

    display->setTextSize(1);

    strcpy_P(buffer, (char *)pgm_read_word(&(unit_str_table[unitIdx])));
    display->print(buffer);

    display->setTextColor(BLACK, WHITE);
    display->setCursor(0, 53);
    display->print(F(" Units "));
    display->setCursor(90, 53);
    display->print(F(" Menu "));
}



byte GUIHomeState::handleInputEvent (byte type, byte val) {
    if (type == eventType::BUTTON_PRESSED) {
        switch (val)
        {
        case buttons::LEFT:
            unitIdx = (unitIdx + 1) % unit_str_table_len;
            break;
        
        case buttons::RIGHT:
            return eventReturn::LAUNCH_MENU;
            break;
        
        default:
            break;
        }
    }
}
