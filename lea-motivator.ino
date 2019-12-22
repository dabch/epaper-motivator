#include <DS3232RTC.h>        // https://github.com/JChristensen/DS3232RTC
#include <Streaming.h>        // http://arduiniana.org/libraries/streaming/
#include <avr/sleep.h>
#include <Adafruit_EPD.h>

#include "compliments.h"

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

//const char CTR_RIGHTALIGN_EXEC = 0x06;
//const char CTR_CENTERALIGN_EXEC = 0x07;


#define MAX_LINE 35
#define WIDTH 212
#define HEIGHT 104
#define MARGIN_TOP 4
#define MARGIN_LEFT 0
//#define MARGIN_LEFT 4
#define CHAR_HEIGHT 14
#define CHAR_WIDTH 12
#define LINE_SPACING 2
const int8_t LINE_DIST = CHAR_HEIGHT + LINE_SPACING;

//#define SHOW_MARGINS

Adafruit_IL0373 display(212, 104, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

int compliment_index = 0;

const uint8_t SQW_PIN(2);     // connect this pin to DS3231 INT/SQW pin

void setup()
{
    Serial.begin(115200);
    
    // initialize the alarms to known values, clear the alarm flags, clear the alarm interrupt flags
    RTC.setAlarm(ALM1_MATCH_DATE, 0, 0, 0, 1);
    RTC.setAlarm(ALM2_MATCH_DATE, 0, 0, 0, 1);
    RTC.alarm(ALARM_1);
    RTC.alarm(ALARM_2);
    RTC.alarmInterrupt(ALARM_1, false);
    RTC.alarmInterrupt(ALARM_2, false);
    RTC.squareWave(SQWAVE_NONE);

    // setSyncProvider() causes the Time library to synchronize with the
    // external RTC by calling RTC.get() every five minutes by default.
//    setSyncProvider(RTC.get);
    RTC.get();
    Serial << "RTC Sync";
    if (timeStatus() != timeSet)
    {
        Serial << " FAIL!";
    }
    Serial << endl;

    printDateTime(RTC.get());
    Serial << " --> Current RTC time\n";

    // configure an interrupt on the falling edge from the SQW pin
    pinMode(SQW_PIN, INPUT_PULLUP);

    // set alarm 1 for 20 seconds after every minute
    RTC.setAlarm(ALM1_MATCH_SECONDS, 20, 0, 0, 1);    // daydate parameter should be between 1 and 7
//    RTC.setAlarm(ALM1_EVERY_SECOND, 20, 0, 0, 1);    // daydate parameter should be between 1 and 7
    RTC.alarm(ALARM_1);                     // ensure RTC interrupt flag is cleared
    RTC.alarmInterrupt(ALARM_1, true);
//digitalWrite(13, HIGH);

    display.begin();

    
    clearBuffer(); 
    
    Serial.println(sizeof('H'));
    //print_compliment(4);
    //display_stream("H""\x81""ello""\x82""\n\x83""bye""\x81""bye");
    display_stream("\x05""He\x01""ll\x02""o\x04\n\x02Obi\x01 stinkt!\n\x03(Ehsan 2019)\x04");
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
    

void loop() {
    delay(1000);
    //go_to_sleep();
    //RTC.alarm(ALARM_1);
    //Serial.println("back up again");
    //printDateTime( RTC.get() );
    //Serial << " --> Alarm 1\n";
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

void go_to_sleep() {
//    digitalWrite(13, LOW);
//    delay(1000);
    attachInterrupt(INT0, wake_up, LOW);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    RTC.alarm(ALARM_1);
    digitalWrite(4, LOW);
    digitalWrite(A4, LOW);
    digitalWrite(A5, LOW);
    delay(100);
    sleep_enable();
    // actually sleep
    sleep_cpu();
    // ----------------------
//    digitalWrite(13, HIGH);
    digitalWrite(4, HIGH);
    Serial.println("just woke up");
}

/* ISR - this guy should be short */
void wake_up() {
    sleep_disable();
    detachInterrupt(INT0);
}

void print_compliment(int8_t index) {
    char buf[MAX_LINE + 1];
    int8_t line_count = compliment_table[index % COMPLIMENT_COUNT].count;
    
    display.setTextColor(EPD_RED);
    display.setTextWrap(true);
    display.setTextSize(2);

    clearBuffer();
    for(uint8_t l = 0; l < line_count; l++) {
        display.setCursor(MARGIN_LEFT, MARGIN_TOP + l * LINE_DIST);
        strcpy_P(buf, compliment_table[index % COMPLIMENT_COUNT].lines[l]);
        display.print(buf);
        display.print("\n");
    }
    display.display();
}


void printDateTime(time_t t)
{
    Serial << ((day(t)<10) ? "0" : "") << _DEC(day(t));
    Serial << monthShortStr(month(t)) << _DEC(year(t)) << ' ';
    Serial << ((hour(t)<10) ? "0" : "") << _DEC(hour(t)) << ':';
    Serial << ((minute(t)<10) ? "0" : "") << _DEC(minute(t)) << ':';
    Serial << ((second(t)<10) ? "0" : "") << _DEC(second(t));
}

void testdrawtext(char *text, uint16_t color) {
    display.setCursor(0, 0);
    display.setTextColor(color);
    display.setTextWrap(true);
    display.print(text);
}
