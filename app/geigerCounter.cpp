#include "geigerCounter.h"


geigerCounter::geigerCounter(settingsContainer& config): 
    CPM(0), CPS(0), uSvPerHr(0),
    mRtPerHr(0), countIdx(0), avgCount(0),
    config(&config)
{
    // Init count buffer
    for (int i = 0; i < MAX_BUFFER; i++) {
        countBuffer[i] = 0;
    }
}


void geigerCounter::update(unsigned long& currentCount) {
    countBuffer[countIdx] = currentCount;
    countIdx++;
    countIdx %= (config->values[0] ? FAST_SAMPLE : SLOW_SAMPLE) + 1;
    avgCount = currentCount - countBuffer[countIdx];
    CPS = (float) avgCount / (config->values[0] ? FAST_SAMPLE : SLOW_SAMPLE);

    if (config->values[2]) {
        CPS = CPS / (1 - CPS * DEADTIME);
    }

    CPM = (float) CPS * 60;
    mRtPerHr = CPS / DOSE_FACTOR;
    uSvPerHr = mRtPerHr * 10;  
}