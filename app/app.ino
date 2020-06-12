// TODO
// Reset geigerCoutner after modifying settings


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>


#include "settingsContainer.h"
#include "geigerCounter.h"
#include "GUIState.h"
#include "GUIHomeState.h"
#include "GUISettingsState.h"
#include "GUIMenuState.h"
#include "GUICountingState.h"
#include "events.h"



/*////////////////////////////////////////////////////////
                      SSD1306 
////////////////////////////////////////////////////////*/
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


/*////////////////////////////////////////////////////////
                      GLOBAL VARS
////////////////////////////////////////////////////////*/
unsigned long currCount = 0;
unsigned long prevCount = 0;
unsigned int  prevMillis = 0;
unsigned long prevMicros = 0;


/*////////////////////////////////////////////////////////
                      ISR STUFF
////////////////////////////////////////////////////////*/
const byte ISRPin = 2;

void ISRCounter() {
    currCount++;
}

/*////////////////////////////////////////////////////////
                      CLICKS STUFF
////////////////////////////////////////////////////////*/
const byte clicksPin = 5;
const byte freq = 44;
const byte clicksTime = 200;


/*////////////////////////////////////////////////////////
                      BUTTONS STUFF
////////////////////////////////////////////////////////*/
const byte debounceDelay = 25;
const byte buttonPins[] = {3, 4};
const byte buttonPinsLen = sizeof(buttonPins) / sizeof(buttonPins[0]);

byte buttonStates[] = {HIGH, HIGH};
byte lastButtonStates[] = {HIGH, HIGH};
unsigned int lastDebounceTimes[] = {0, 0};



/*////////////////////////////////////////////////////////
                      CHAR BUFFERR
////////////////////////////////////////////////////////*/
#define CHAR_BUFFER_LEN 15
char charBuffer[CHAR_BUFFER_LEN];




/*////////////////////////////////////////////////////////
                      GUI AND SETTINGS
////////////////////////////////////////////////////////*/
GUIState* currentState;
settingsContainer config(0x0, 3);
geigerCounter counter(config);
GUIHomeState homeState(display, counter);
GUISettingsState settingsState(display, config);
GUIMenuState menuState (display);
GUICountingState countingState(display);




/*////////////////////////////////////////////////////////
                      ARDUINO INIT
////////////////////////////////////////////////////////*/
void setup() {
    Serial.begin(9600);

    // OLED setup, block if mem alloc failed
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }


    // Init button buttonPins
    for (int i = 0; i < buttonPinsLen; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
    
    currentState = &homeState; 

    // Init Geiger pin
    pinMode(ISRPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ISRPin), ISRCounter, FALLING);

    // Init countBuffer
    for (int i = 0; i < CHAR_BUFFER_LEN; i++) {
        charBuffer[i] = '\0';
    }
}




/*////////////////////////////////////////////////////////
                      MAIN LOOP
////////////////////////////////////////////////////////*/
void loop() {
    // Debounce section
    for (int i = 0; i < buttonPinsLen; i++) {
        byte r = digitalRead(buttonPins[i]);

        // A change in state has been made, restart timer
        if (r != lastButtonStates[i]) {
            lastDebounceTimes[i] = millis();
        }

        // If that change's duration is longer than the debounce time, 
        // we might have a button press
        if ((millis() - lastDebounceTimes[i]) > debounceDelay) {

            // check current button state
            if (r != buttonStates[i]) {
                buttonStates[i] = r;

                // Buttons in pullup configuration
                if (buttonStates[i] == HIGH) {
                    int er = currentState->handleInputEvent(eventType::BUTTON_PRESSED, i);
                    handleEventReturns(er);
                }
            }
        }

        lastButtonStates[i] = r;
    }



    // Update counter inner attributes
    if (millis() - prevMillis >= 1000) {
        counter.update(currCount);
        prevMillis = millis();        
    }
    countingState.update(currCount);
        

    // Trigger clicks if option is toggled
    if (config.values[1]) {
        if (currCount > prevCount) {
            tone(clicksPin, freq);
            prevCount = currCount;
            prevMicros = micros();
       
        }

        if (micros() - prevMicros > clicksTime) {
            noTone(clicksPin);
            prevMicros = micros();
        }
    }

    

    //drawing section
    display.clearDisplay();
    currentState->draw(charBuffer);
    display.display();
}



void handleEventReturns(byte er) {
    switch (er) {
        case eventReturn::LAUNCH_HOMESCREEN:
            currentState = (GUIState*) &homeState;
            break;

        case eventReturn::LAUNCH_SETTINGS:
            currentState = (GUIState*) &settingsState;
            break;

        case eventReturn::LAUNCH_MENU:
            currentState = (GUIState*) &menuState;
            break;
        
        case eventReturn::LAUNCH_COUNTING:
            currentState = (GUIState*) &countingState;
            break;
        
        default:
            break;
    }
}