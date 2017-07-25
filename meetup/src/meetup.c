#include "meetup.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

int weekday_in_week(const struct tm start, int weekday) {
    for(struct tm day = start; day.tm_mday - start.tm_mday < 7; day.tm_mday++) {
        mktime(&day);
        printf("%04d-%02d-%02d: (%d/%d)\n", day.tm_year, day.tm_mon, day.tm_mday, day.tm_wday, weekday);
        if(day.tm_wday == weekday)
            return day.tm_mday;
    }
    return -1;
}

int weekday_to_int(const char *weekday) {
    if(strcmp(weekday, "Wednesday") == 0)
        return 0;
    else if(strcmp(weekday, "Thursday") == 0)
        return 1;
    else if(strcmp(weekday, "Friday") == 0)
        return 2;
    else if(strcmp(weekday, "Saturday") == 0)
        return 3;
    else if(strcmp(weekday, "Sunday") == 0)
        return 4;
    else if(strcmp(weekday, "Monday") == 0)
        return 5;
    else if(strcmp(weekday, "Tuesday") == 0)
        return 6;
    return -1;
}

int meetupDayOfMonth(int year, int month, const char* week, const char* dayOfWeek) {
    struct tm date = { .tm_min = 0, .tm_hour = 0, .tm_sec = 1, .tm_year = year,
        .tm_mon = month };
    int weekday;

    if(strcmp(week, "first") == 0)
        date.tm_mday = 1;
    else if(strcmp(week, "second") == 0)
        date.tm_mday = 8;
    else if(strcmp(week, "second") == 0)
        date.tm_mday = 15;
    else if(strcmp(week, "third") == 0)
        date.tm_mday = 22;
    else if(strcmp(week, "fourth") == 0)
        date.tm_mday = 29;
    else if(strcmp(week, "teenth") == 0)
        date.tm_mday = 13;
    else if(dayOfWeek && strcmp(week, "last") == 0) {
        return -1;
    } else
        return -1;

    weekday = weekday_to_int(dayOfWeek);
    return weekday_in_week(date, weekday);
}
