#ifndef COMPLIMENT_H
#define COMPLIMENT_H

typedef struct day {
    int8_t day_of_month;
    int8_t month;
    char *compliment;
} day_t;


const char U_UMLAUT = 0x81;
const char A_UMLAUT = 0x84;
const char O_UMLAUT = 0x94;
const char A_UMLAUT_CAP = 0x8e;
const char U_UMLAUT_CAP = 0x9a;
const char O_UMLAUT_CAP = 0x99;
const char S_UMLAUT = 0;

#include "bare_compliments.h"

const char merry_xmas[] PROGMEM = "\x05\n\n\nFrohe Weihnachten!\x04";
const char guten_rutsch[] PROGMEM = "\n\x05\x02Guten Rutsch!\n\x01(aber nimm's\nnicht zu\nw\x94rtlich!)\x04";
const char happy_new_year[] PROGMEM = "\x05\x02\n\nFrohes neues Jahr!\x04";
const char happy_birthday[] PROGMEM = "\x05""\x02""Alles gute zum\nGeburtstag!\x01\n\nBleib wie du bist\nund lass dich\nfeiern!\x04";

const day_t special_days[] = {
    {19, 1, happy_birthday},
    {24, 12, merry_xmas},
    {31, 12, guten_rutsch},
    {1, 1, happy_new_year},
    {30, 12, happy_new_year},
};

const int SPECIAL_DAY_COUNT = 5;

#endif
