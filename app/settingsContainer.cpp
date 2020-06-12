#include "settingsContainer.h"
#include <EEPROM.h>

settingsContainer::settingsContainer (int addr, byte n) : 
    addr(addr),
    n(n) 
{

    #ifdef FIRST_RUN
    for (int i = 0; i < n; i++) {
        EEPROM.put(addr + sizeof(bool) * i, false);
    }
    #endif

    load();
}

void settingsContainer::load() {
    for (byte i = 0; i < n; i++) {
        EEPROM.get(addr + sizeof(bool) * i, values[i]);
    }

}

void settingsContainer::save() {
    for (byte i = 0; i < n; i++) {
        EEPROM.put(addr + sizeof(bool) * i, values[i]);
    }
}