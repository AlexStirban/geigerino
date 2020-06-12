#ifndef STRINGSTABLE_H
#define STRINGSTABLE_H

#include <avr/pgmspace.h>

// Strings for units
const char unit_str_0[] PROGMEM = "CPM";
const char unit_str_1[] PROGMEM = "CPS";
const char unit_str_2[] PROGMEM = "uSV/hr";
const char unit_str_3[] PROGMEM = "mRt/hr";

// Strings for settings options
const char sett_str_0[] PROGMEM = "Fast averaging";
const char sett_str_1[] PROGMEM = "Click";
const char sett_str_2[] PROGMEM = "Dead time fix";
const char sett_str_3[] PROGMEM = "Save & Exit";

// Strings for menu options
const char menu_str_0[] PROGMEM = "Measure counts";
const char menu_str_1[] PROGMEM = "Settings";
const char menu_str_2[] PROGMEM = "Exit";

// Strings for counting
const char count_str_0[] PROGMEM = "Time";
const char count_str_1[] PROGMEM = "Num. Counts";
const char count_str_2[] PROGMEM = "New Count";
const char count_str_3[] PROGMEM = "Exit";

 
// String tables
const char *const unit_str_table[] PROGMEM = {unit_str_0, unit_str_1, unit_str_2, unit_str_3};
const char *const sett_str_table[] PROGMEM = {sett_str_0, sett_str_1, sett_str_2, sett_str_3};
const char *const menu_str_table[] PROGMEM = {menu_str_0, menu_str_1, menu_str_2};
const char *const counting_str_table[] PROGMEM = {count_str_0, count_str_1, count_str_2, count_str_3};

// String table len
const int unit_str_table_len = sizeof(unit_str_table) / sizeof(unit_str_table[0]);
const int sett_str_table_len = sizeof(sett_str_table) / sizeof(sett_str_table[0]);
const int menu_str_table_len = sizeof(menu_str_table) / sizeof(menu_str_table[0]);
const int counting_str_table_len = sizeof(counting_str_table) / sizeof(counting_str_table[0]);

#endif