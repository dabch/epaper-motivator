#ifndef EPD_DISPLAY_H
#define EPD_DISPLAY_H

#include <Arduino.h>
#include <Adafruit_EPD.h>


#define EPD_CS    10
#define EPD_DC     9
#define SRAM_CS    8
#define SD_CS        6
#define EPD_RESET -1
#define EPD_BUSY 4

const char CTR_BLACK = 0x01;
const char CTR_RED   = 0x02;
const char CTR_RIGHTALIGN = 0x03;
const char CTR_LEFTALIGN = 0x04;
const char CTR_CENTERALIGN = 0x05;
const char CTR_ALIGN_EXECUTE = 0x06;


#define MAX_LINE 35
#define WIDTH 212
#define HEIGHT 104
#define MARGIN_TOP 5
//#define MARGIN_LEFT 0
#define MARGIN_LEFT 4
#define CHAR_HEIGHT 14
#define CHAR_WIDTH 12
#define LINE_SPACING 2
const int8_t LINE_DIST = CHAR_HEIGHT + LINE_SPACING;

//#define SHOW_MARGINS

extern Adafruit_IL0373 display;//(212, 104, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

void init_display();
void display_init();


void clearBuffer();

void display_stream(char *str);

#endif
