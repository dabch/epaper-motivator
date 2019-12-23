#include <DS3232RTC.h>        // https://github.com/JChristensen/DS3232RTC
#include <Streaming.h>        // http://arduiniana.org/libraries/streaming/
#include <avr/sleep.h>
//#include <Adafruit_EPD.h>

#include "src/compliments.h"
#include "src/epd_display.h"
#include "src/rtc_alarm.h"

int compliment_index = 0;


void setup()
{
    Serial.begin(115200);
    
    init_rtc();
    init_display();
   
    display_stream("\x05""He\x01""ll\x02""o World\x04\n\x02Obi\x01 was geht?!\n\x03(Ehsan 2019)\x04\nLeft\x03Right\x04\n\x05""Center\x04\nbottom");
}


    

void loop() {
    delay(1000);
    //go_to_sleep();
    //RTC.alarm(ALARM_1);
    //Serial.println("back up again");
    //printDateTime( RTC.get() );
    //Serial << " --> Alarm 1\n";
}

