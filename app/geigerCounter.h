#ifndef GEIGERCOUNTER_H
#define GEIGERCOUNTER_H

#define SLOW_SAMPLE 30
#define FAST_SAMPLE 10
#define MAX_BUFFER 30

// Dead time (in seconds)
#define DEADTIME  0.0000190
#define DOSE_FACTOR  25.5


#include <Arduino.h>
#include "settingsContainer.h"

class geigerCounter {
    private:
        settingsContainer* config;
        byte countIdx;
        unsigned int  avgCount;
        unsigned long countBuffer[MAX_BUFFER + 1];
        

    public:
        unsigned int CPM;
        float CPS;
        float uSvPerHr;
        float mRtPerHr;

    public:
        geigerCounter(settingsContainer& config);
        void update(unsigned long& currentCount);
};
#endif