# epaper-motivator
Ultra-low power Arduino displaying motivational quotes on an e-ink screen

This Arduino project displays a different motivational quote every day using a small 2.1" two-color e-ink screen by Waveshare.
The quotes are stored in EEPROM and shuffled upon startup.

To run for extended periods on AA batteries (up to 6 months), several power saving
measures are taken: For one, Hardware modifications were made (such as removal of power LEDs and the use of a 3.3v Arduino without USB chip). Most importantly,
the Arduino is in deep sleep (`SLEEP_MODE_PWR_DOWN`) and only wakes up every 24 hours to update the e-ink screen. For waking up, a DS3231
RTC module is attached to a hardware interrupt pin. This setups achieves a power draw of less than **0.75mA when in deep sleep**.
