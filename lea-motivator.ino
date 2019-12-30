#include <DS3232RTC.h>        // https://github.com/JChristensen/DS3232RTC
#include <Streaming.h>        // http://arduiniana.org/libraries/streaming/
#include <avr/sleep.h>
#include <stdlib.h>

#include "src/compliments.h"
#include "src/epd_display.h"
#include "src/rtc_alarm.h"
#include "src/shuffle.h"

int compliment_index = 0;

char *compliments_shuffled[COMPLIMENT_COUNT];
int16_t compliment_id = 6;

void setup()
{
    Serial.begin(9600);
    
    init_rtc();
    init_display();

    // seed the PRNG with unix time to get a different random sequence each reset
    srand(now());

    // shuffle our compliment list
    memcpy(compliments_shuffled, compliments_progmem, COMPLIMENT_COUNT * sizeof(char *));
    //shuffle_ptr_array(compliments_shuffled, COMPLIMENT_COUNT);

    for(int i = 0; i < COMPLIMENT_COUNT; i++) {
        char buf[256];
        strcpy_P(buf, compliments_shuffled[i]);
        Serial << buf  << endl;
    }

   
    //display_stream("\x05""He\x01""ll\x02""o World\x04\n\x02Obi\x01 was geht?!\n\x03(Ehsan 2019)\x04\nLeft\x03Right\x04\n\x05""Center\x04\nbottom");
}

void loop() {
    char *ptr = check_special_day();
    if(!ptr)
        ptr = compliments_shuffled[compliment_id++ % COMPLIMENT_COUNT];

    show_compliment(ptr); 
    Serial << "going to sleep" << endl;
    go_to_sleep();
    Serial << "woke up" << endl;

}

char *check_special_day() {
    for(int16_t i = 0; i < SPECIAL_DAY_COUNT; i++) {
        if(special_days[i].month == month() && special_days[i].day_of_month == day())
            return special_days[i].compliment;
    }
    return NULL;
}

void show_compliment(char *ptr) {
    char buf[256];
    strcpy_P(buf, ptr);
    display_stream(buf);
}
