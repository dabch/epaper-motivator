#include <Adafruit_EPD.h>
#include <Streaming.h>
#include "epd_display.h"

Adafruit_IL0373 display(212, 104, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

void init_display() {
    display.begin();
    clearBuffer(); 
}

void clearBuffer() {
    display.clearBuffer();
#ifdef SHOW_MARGINS
    display.drawFastHLine(0, MARGIN_TOP, WIDTH, EPD_BLACK);
    display.drawFastHLine(0, HEIGHT - MARGIN_TOP, WIDTH, EPD_BLACK);
    display.drawFastVLine(MARGIN_LEFT, 0, HEIGHT, EPD_BLACK);
    display.drawFastVLine(WIDTH - MARGIN_LEFT, 0, HEIGHT, EPD_BLACK);
#endif
}


void display_stream(char *str) {
    display.setTextColor(EPD_RED);
    display.setTextWrap(true);
    display.setTextSize(2);
    
    display.setCursor(MARGIN_LEFT, MARGIN_TOP);

    Serial.println("printing via display_stream()");

    int8_t current_line = 0;
    int8_t current_char = 0;

    char *ptr = str;
    Serial.println(sizeof(*ptr));
    char *align_begin;
    char *align_end;
    char align_mode = CTR_LEFTALIGN;
    
    int16_t controls;

    while(*ptr) {
        Serial.print(*ptr, HEX);
        Serial.print(" mode ");
        Serial.println(align_mode, HEX);
        switch(align_mode) {
            case CTR_LEFTALIGN:
                if(*ptr == '\n') {
                    int16_t x = MARGIN_LEFT;
                    int16_t y = MARGIN_TOP + ++current_line * LINE_DIST;
                    display.setCursor(x, y);
                } else if(*ptr == CTR_BLACK) {
                    Serial.println("BLACK");
                    display.setTextColor(EPD_BLACK); 
                } else if(*ptr == CTR_RED) {
                    Serial.println("RED");
                    display.setTextColor(EPD_RED); 
                } else if(*ptr == CTR_RIGHTALIGN) {
                    Serial.println("beginning to right align");
                    align_begin = ptr + 1; // inclusive!  
                    align_mode = CTR_RIGHTALIGN;
                    controls = 0;
                } else if(*ptr == CTR_CENTERALIGN) {
                    Serial.println("beginning to center align");
                    align_begin = ptr + 1; // inclusive!  
                    align_mode = CTR_CENTERALIGN;
                    controls = 0;
                } else {
                    display.write(*ptr);
                }
                ptr++;
                break;
            case CTR_RIGHTALIGN:
                if(*ptr == '\n') {
                    Serial.println("Rightalign newline not supported!");
                } else if(*ptr == CTR_BLACK || *ptr == CTR_RED) {
                    controls++;
                } else if(*ptr == CTR_LEFTALIGN) {
                    Serial.println("end found");
                    align_end = ptr;
                    Serial << "difference: " << ptr - align_begin -1 << endl;
                    Serial << "count: " << (ptr - align_begin) << endl;
                    int16_t x = WIDTH - MARGIN_LEFT - CHAR_WIDTH * (ptr - align_begin - controls);
                    int16_t y = MARGIN_TOP + current_line * LINE_DIST;
                    Serial << x << " - " << y << endl;
                    display.setCursor(x, y);
                    ptr = align_begin;
                    align_mode = CTR_ALIGN_EXECUTE;
                    break;
                }
                ptr++;
                break;
            case CTR_CENTERALIGN:
                if(*ptr == '\n') {
                    Serial.println("Center align newline not supported!");
                } else if(*ptr == CTR_BLACK || *ptr == CTR_RED) {
                    controls++;
                } else if(*ptr == CTR_LEFTALIGN) {
                    Serial.println("end found");
                    align_end = ptr;
                    Serial << "difference: " << ptr - align_begin -1 << endl;
                    Serial << "count: " << (ptr - align_begin) << endl;
                    int16_t x = (WIDTH - CHAR_WIDTH * (ptr - align_begin - controls)) / 2;
                    int16_t y = MARGIN_TOP + current_line * LINE_DIST;
                    Serial << x << " - " << y << endl;
                    display.setCursor(x, y);
                    ptr = align_begin;
                    align_mode = CTR_ALIGN_EXECUTE;
                    break;
                }
                ptr++;
                break;
            case CTR_ALIGN_EXECUTE:
                if(*ptr == CTR_LEFTALIGN) {
                    ptr = align_end + 1;
                    align_mode = CTR_LEFTALIGN;
                    break;
                } else if(*ptr == CTR_BLACK)
                    display.setTextColor(EPD_BLACK);
                else if(*ptr == CTR_RED)
                    display.setTextColor(EPD_RED);
                else
                    display.write(*ptr);
                ptr++;
                break;
            default:
                Serial.print(align_mode, HEX);
                Serial.println(": invalid case triggered");
                break;
        }
    }
    Serial.println("printing via display_stream() done");
    display.display();
}


