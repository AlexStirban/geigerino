#include "GUICountingState.h"

#include "stringsTable.h"
#include "events.h"
#include "inputs.h"


GUICountingState::GUICountingState(Adafruit_SSD1306& display) :
    GUIState(display), countingIdx(0),
    prevMillis(0), curr(0), prev(0),
    deltaTime(10), isCounting(false),
    deltaCount(0), scrollingIdx(0),
    ncounts(0), n(0)
{

}



void GUICountingState::draw(char* buffer) const {
    display->setTextColor(WHITE);
    display->drawRect(0, 0, 128, 16, WHITE);

    // HEADER
    display->setCursor(4, 4);
    display->setTextColor(WHITE);
    display->print(F("Count: "));
    display->setCursor(110, 4);
    display->print(deltaCount);

    // PRINT SETTINGS
    display->setCursor(0, 20);
    
    // Scroll text vertically with software, not supported through hardware
    for (byte i = scrollingIdx; i < counting_str_table_len - 1 + scrollingIdx; i++) {
        if (countingIdx == i && !isCounting) {
            display->setTextColor(BLACK, WHITE);
        }
        else {
            display->setTextColor(WHITE);
        }
        strcpy_P(buffer, (char *)pgm_read_word(&(counting_str_table[i])));
        display->print(buffer);
        

        if (i == 0) {
            display->setCursor(110, display->getCursorY());
            display->print(deltaTime);
        }

        if (i == 1) {
            display->setCursor(110, display->getCursorY());
            display->print(ncounts);
        }
     
        display->print(F("\n"));
    } 

    // Progress bar
    if (isCounting) {
        float p = 0;

        // If we're making only one measure
        if (ncounts == 0) {
            p = (float) (millis() - prevMillis) / (1000 * deltaTime);
            p = p > 1 ? 1 : p; // Clamp to 1 
        }

        // If we're making multiple measures over serial
        else {
            p =  (float) (1 -  (float) n / ncounts);
        }


        display->fillRect(0, 50, p * 108, 8, WHITE);
        display->setCursor(108, display->getCursorY() + 6);
        display->print((byte) (p * 100));
        display->print(F("%"));

    }
}

void GUICountingState::update(unsigned long& currentCount) {
    curr = currentCount;

    if (isCounting) {
        if (millis() - prevMillis >=  deltaTime * 1000) {
            deltaCount = curr - prev;

            if (ncounts > 0 && n > 0) {
                Serial.println(deltaCount);


                prev = curr;
                prevMillis = millis();
                n--;
            }
            else {
                isCounting = false;
            }
            
        }

    }
}

byte GUICountingState::handleInputEvent(byte type, byte val) {
    if (!isCounting) {
        switch(val) {
            case buttons::LEFT:
                countingIdx = (countingIdx + 1) % counting_str_table_len;

                if (scrollingIdx == 0 && countingIdx == counting_str_table_len - 1) {
                    scrollingIdx = 1;
                }
                else if (scrollingIdx == 1 && countingIdx == 0) {
                    scrollingIdx = 0;
                }
                break;

            case buttons::RIGHT:
                switch (countingIdx)
                {
                    case 0:
                        deltaTime += (deltaTime == 250) ? -240 : 10;
                        break;
                    

                    case 1:
                        ncounts = (ncounts + 50) % 300;
                        break;

                    case 2:
                        n = ncounts;
                        deltaCount = 0;
                        prev = curr;
                        prevMillis = millis();
                        isCounting = true;
                        break;

                    case 3:
                        return eventReturn::LAUNCH_MENU;
                        break;

                    default:
                        break;
                }
                break;
            
            default:
                break;     
        }
    }

    return eventReturn::NO_ACTION;
}