#include "GUISettingsState.h"
#include "events.h"
#include "inputs.h"
#include "stringsTable.h"

GUISettingsState::GUISettingsState(Adafruit_SSD1306& display, settingsContainer& config):
    GUIState(display),
    config(&config),
    settingIdx(0)
{

}


void GUISettingsState::draw(char* buffer) const {
    display->setTextColor(WHITE);
    display->drawRect(0, 0, 128, 16, WHITE);

    // HEADER
    display->setCursor(4, 4);
    display->setTextColor(WHITE);
    display->print(F("Settings"));

    // PRINT SETTINGS
    display->setCursor(0, 20);


    for (byte i = 0; i < sett_str_table_len; i++) {
        if (settingIdx == i) {
            display->setTextColor(BLACK, WHITE);
        }
        else {
            display->setTextColor(WHITE);
        }
        strcpy_P(buffer, (char *)pgm_read_word(&(sett_str_table[i])));
        display->print(buffer);

        
        if (i < sett_str_table_len - 1) {
            display->setTextColor(WHITE);
            display->setCursor(120, display->getCursorY());
            display->print(config->values[i]);
            display->print(F("\n"));
        }
    } 
}
 
 
 
 
byte GUISettingsState::handleInputEvent(byte type, byte val) {
    switch(val) {
        case buttons::LEFT:
            settingIdx = (settingIdx + 1) % sett_str_table_len ;
            break;
            
        case buttons::RIGHT:
            if (settingIdx < config->n) {
                config->values[settingIdx] = !config->values[settingIdx];
            }
            else{
                // Save and exit
                config->save();
                settingIdx = 0;
                return eventReturn::LAUNCH_MENU;
            }    
            break;

        default:
            break;
    }

    return eventReturn::NO_ACTION;
} 