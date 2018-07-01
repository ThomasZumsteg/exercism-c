#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

#define MAX_LEN 256

void thousands(long digits, char *buffer) {
    char tmp[MAX_LEN];

    char *teens[] = { "ten", "eleven", "twelve", "thirteen", "fourteen",
        "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
    char *tens[] = { "", "ten", "twenty", "thirty", "fourty", "fifty", "sixty",
        "seventy", "eighty", "ninty" };
    char *ones[] = { "", "one", "two", "three", "four", "five", "six", "seven",
        "eight", "nine" };

    long one = digits % 10;
    long ten = (digits % 100) / 10;
    long hundered = (digits % 1000) / 100;

    if(hundered != 0 && ten == 0 && one == 0)
        sprintf(tmp, "%s hundred", ones[hundered]);
    else if(hundered != 0 && ten == 1)
        sprintf(tmp, "%s hundred %s", ones[hundered], teens[ten]);
    else if(hundered != 0 && ten > 1 && one == 0)
        sprintf(tmp, "%s hundred %s", ones[hundered], tens[ten]);
    else if(hundered != 0 && ten > 1 && one != 0)
        sprintf(tmp, "%s hundred %s-%s", ones[hundered], tens[ten], ones[one]);
    else if(hundered == 0 && ten == 1)
        sprintf(tmp, "%s", teens[one]);
    else if(hundered == 0 && ten > 1 && one != 0)
        sprintf(tmp, "%s-%s", tens[ten], ones[one]);
    else if(hundered == 0 && ten > 1 && one == 0)
        sprintf(tmp, "%s", tens[ten]);
    else if(hundered == 0 && ten == 0 && one != 0)
        sprintf(tmp, "%s", ones[one]);
    strcat(buffer, tmp);
}

int say(long number, char **buffer) {
    *buffer = calloc(sizeof(char *), MAX_LEN);
    if(number == 0) {
        *buffer = strdup("zero");
        return 0;
    }
    thousands(number, *buffer);
    return 0;
}
