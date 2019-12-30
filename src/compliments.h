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

/*

const char c0[] PROGMEM = "Du bist die Geilste!!";
const char c1[] PROGMEM = "Obi halts Maul!\n\x03(Ehsan M.)\x04";
const char c2[] PROGMEM = "\n\x05So nen \x02h\x81""bschen Hut\x04\n\x01 h\x84tt ich auch gerne!";
const char c3[] PROGMEM = "Test 4";
const char c4[] PROGMEM = "Test 5";
const char c5[] PROGMEM = "\n\x05wAs EssEn wIr\x04\n\x05hEUtE?\x04\n\n\x05(Obi, \x02jeden\x01 Tag)\x04";
const char c6[] PROGMEM = "\x05he\x02l\x01lo\nbye\x02""bye\x04";

const char *const compliments_progmem[] = {c0, c1, c2, c3, c4, c5, c6};

const int COMPLIMENT_COUNT = 7;

*/
#include "bare_compliments.h"

const char merry_xmas[] PROGMEM = "\x05\n\n\nFrohe Weihnachten!\x04";
const char guten_rutsch[] PROGMEM = "\n\x05\x02Guten Rutsch!\n\x01(aber nimm's\nnicht zu\nw\x94rtlich! ;) )\x04";
const char happy_new_year[] PROGMEM = "\x05\x02\n\nFrohes neues Jahr!\x04";

const day_t special_days[] = {
    {24, 12, merry_xmas},
    {31, 12, guten_rutsch},
    {1, 1, happy_new_year},
    {30, 12, happy_new_year},
};

const int SPECIAL_DAY_COUNT = 2;

#endif
