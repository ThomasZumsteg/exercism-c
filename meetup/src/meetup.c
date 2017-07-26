#include "meetup.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

int weekday_in_week(const struct tm start, int month, int weekday, int diff) {
    for(struct tm day = start;
            abs(day.tm_mday - start.tm_mday) < 7 && month - 1 == day.tm_mon;
            day.tm_mday += diff) {
        mktime(&day);
        if(day.tm_wday == weekday)
            return day.tm_mday;
    }
    return 0; // No date found
}

int weekday_to_int(const char *weekday) {
    if(strcmp(weekday, "Saturday") == 0)
        return 0;
    else if(strcmp(weekday, "Sunday") == 0)
        return 1;
    else if(strcmp(weekday, "Monday") == 0)
        return 2;
    else if(strcmp(weekday, "Tuesday") == 0)
        return 3;
    else if(strcmp(weekday, "Wednesday") == 0)
        return 4;
    else if(strcmp(weekday, "Thursday") == 0)
        return 5;
    else if(strcmp(weekday, "Friday") == 0)
        return 6;
    return -1; // Error
}

int meetupDayOfMonth(int year, int month, const char* week, const char* dayOfWeek) {
    struct tm date = { .tm_min = 0, .tm_hour = 0, .tm_sec = 0, .tm_year = year,
        .tm_mon = month - 1 };
    int weekday = weekday_to_int(dayOfWeek), diff = 1;

    if(strcmp(week, "first") == 0)
        date.tm_mday = 1;
    else if(strcmp(week, "second") == 0)
        date.tm_mday = 8;
    else if(strcmp(week, "third") == 0)
        date.tm_mday = 15;
    else if(strcmp(week, "fourth") == 0)
        date.tm_mday = 22;
    else if(strcmp(week, "fifth") == 0)
        date.tm_mday = 29;
    else if(strcmp(week, "teenth") == 0)
        date.tm_mday = 13;
    else if(strcmp(week, "last") == 0) {
        date.tm_mon++;
        date.tm_mday = 0;
        diff = -1;
    } else
        return -1;  // Error

    mktime(&date);
    return weekday_in_week(date, month, weekday, diff);
}
