#include "rtc_alarm.h"
#include <DS3232RTC.h>
#include <Arduino.h>
#include <avr/sleep.h>
#include <Streaming.h>

void init_rtc() {
    // initialize the alarms to known values, clear the alarm flags, clear the alarm interrupt flags
    RTC.setAlarm(ALM1_MATCH_DATE, 0, 0, 0, 1);
    RTC.setAlarm(ALM2_MATCH_DATE, 0, 0, 0, 1);
    RTC.alarm(ALARM_1);
    RTC.alarm(ALARM_2);
    RTC.alarmInterrupt(ALARM_1, false);
    RTC.alarmInterrupt(ALARM_2, false);
    RTC.squareWave(SQWAVE_NONE);

    setSyncProvider(RTC.get);
    Serial << "RTC Sync";
    if (timeStatus() != timeSet)
    {
        Serial << " FAIL!";
    }
    Serial << endl;

    printDateTime(RTC.get());
    Serial << " --> Current RTC time: " << now() << endl;

    // configure the pin, but don't attach interrupt yet. This is done when going to sleep
    pinMode(SQW_PIN, INPUT_PULLUP);

}

void go_to_sleep() {
    // set alarm 1 for 20 seconds after every minute
    RTC.setAlarm(ALM1_MATCH_HOURS, 0, 30, 3, 1);    // daydate parameter should be between 1 and 7
    //RTC.setAlarm(ALM1_MATCH_SECONDS, 0, 30, 3, 1);    // daydate parameter should be between 1 and 7
    RTC.alarm(ALARM_1);                     // ensure RTC interrupt flag is cleared
    RTC.alarmInterrupt(ALARM_1, true);
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

void printDateTime(time_t t)
{
    Serial << ((day(t)<10) ? "0" : "") << _DEC(day(t));
    Serial << monthShortStr(month(t)) << _DEC(year(t)) << ' ';
    Serial << ((hour(t)<10) ? "0" : "") << _DEC(hour(t)) << ':';
    Serial << ((minute(t)<10) ? "0" : "") << _DEC(minute(t)) << ':';
    Serial << ((second(t)<10) ? "0" : "") << _DEC(second(t));
}

