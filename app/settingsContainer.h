#ifndef SETTINGSCONTAINER_H
#define SETTINGSCONTAINER_H

#define MAX_SETTINGS_SLOTS 3

#include <Arduino.h>

class settingsContainer {
  private:
    byte addr;

  public:
    byte n;
    bool values[MAX_SETTINGS_SLOTS];

  public:
    settingsContainer(int addr, byte n);

    void load();
    void save();
};

#endif