#ifndef RTC_ALARM_H
#define RTC_ALARM_H
#include <Arduino.h>
#include <DS3232RTC.h>

const uint8_t SQW_PIN = 2;    // connect this pin to DS3231 INT/SQW pin

void init_rtc();

void go_to_sleep();

void wake_up();

void printDateTime(time_t t);

#endif
