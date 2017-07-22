#include "clock.h"
#include <stdio.h>

#define CLOCK_FMT  "%02d:%02d"

void clock(time_text_t time_text, int hour, int minute) {
    hour += minute / 60;
    minute = minute % 60;
    if(minute < 0) {
        minute += 60;
        hour--;
    }

    hour = hour % 24;
    if( hour < 0 ) hour += 24;

    sprintf(time_text, CLOCK_FMT, hour, minute);
}

void clock_add(time_text_t time_text, int minute_offset) {
    int hour, minute;
    sscanf(time_text, CLOCK_FMT, &hour, &minute);
    clock(time_text, hour, minute + minute_offset);
}
