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
int16_t compliment_id = 0;

void setup()
{
    Serial.begin(9600);
    
    Serial << "init rtc... ";
    init_rtc();
    Serial << "done." << endl << "init display... ";
    init_display();
    Serial << "done." << endl;

    // seed the PRNG with unix time to get a different random sequence each reset
    srand(now());

    // shuffle our compliment list
    Serial << "memcpying compliment list... ";
    memcpy(compliments_shuffled, compliments_progmem, COMPLIMENT_COUNT * sizeof(char *));
    Serial << "done" << endl << "shuffling list.. ";
    shuffle_ptr_array(compliments_shuffled, COMPLIMENT_COUNT);
    Serial << "init done.";

/*    for(int i = 0; i < COMPLIMENT_COUNT; i++) {
        char buf[256];
        strcpy_P(buf, compliments_shuffled[i]);
        Serial << buf  << endl;
    }*/
}

void loop() {
    Serial << "beginning loop" << endl;
    char *ptr = check_special_day();
    Serial << "special ptr: " << (ptr == NULL) << endl;
    if(!ptr)
        ptr = compliments_shuffled[compliment_id++ % COMPLIMENT_COUNT];


    show_compliment(ptr); 
    Serial << "going to sleep" << endl;
    go_to_sleep();
    Serial << "woke up" << endl;

    if(compliment_id >= COMPLIMENT_COUNT) {
        Serial << "reshuffling ptr array" << endl;
        shuffle_ptr_array(compliments_shuffled, COMPLIMENT_COUNT);
        compliment_id = 0;
    }

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
    Serial << "buffer: "<<  buf << endl;
    display_stream(buf);
}
