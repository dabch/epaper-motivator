#ifndef COMPLIMENT_H
#define COMPLIMENT_H

const char U_UMLAUT = 0x81;
const char A_UMLAUT = 0x84;
const char O_UMLAUT = 0x94;
const char A_UMLAUT_CAP = 0x8e;
const char U_UMLAUT_CAP = 0x9a;
const char O_UMLAUT_CAP = 0x99;


const char c0[] PROGMEM = "Du bist die Geilste!!";
const char c1[] PROGMEM = "Obi halts Maul!\n\x03(Ehsan M.)\x04";
const char c2[] PROGMEM = "\n\x05So nen \x02h\x81""bschen Hut\x04\n\x01 h\x84tt ich auch gerne!";
const char c3[] PROGMEM = "Test 4";
const char c4[] PROGMEM = "Test 5";
const char c5[] PROGMEM = "\n\x05wAs EssEn wIr\x04\n\x05hEUtE?\x04\n\n\x05(Obi, \x02jeden\x01 Tag)\x04";
const char c6[] PROGMEM = "\x05he\x02l\x01lo\nbye\x02""bye\x04";

const char *const compliments_progmem[] = {c0, c1, c2, c3, c4, c5, c6};

const int COMPLIMENT_COUNT = 7;

#endif
