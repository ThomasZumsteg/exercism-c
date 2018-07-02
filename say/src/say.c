#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

#define MAX_LEN 512

char *teens[] = { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
    "sixteen", "seventeen", "eighteen", "nineteen" };
char *tens[] = { "", "ten", "twenty", "thirty", "forty", "fifty", "sixty",
    "seventy", "eighty", "ninty" };
char *ones[] = { "", "one", "two", "three", "four", "five", "six", "seven",
    "eight", "nine" };

char *powers[] = { "", " thousand", " million", " billion", " trillion" };

char *thousands(long digits) {
    char *tmp = calloc(sizeof(char), MAX_LEN);

    long one = digits % 10;
    long ten = (digits % 100) / 10;
    long hundered = (digits % 1000) / 100;

    if(hundered != 0 && ten == 0 && one == 0)
        sprintf(tmp, "%s hundred", ones[hundered]);
    else if(hundered != 0 && ten == 1)
        sprintf(tmp, "%s hundred %s", ones[hundered], teens[one]);
    else if(hundered != 0 && ten > 1 && one == 0)
        sprintf(tmp, "%s hundred %s", ones[hundered], tens[one]);
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
    return tmp;
}

void strpre(char *dst, char *src) {
    char *tmp = calloc(sizeof(char), strlen(dst)+ strlen(src));
    strcpy(tmp, src);
    strcat(tmp, dst);
    strcpy(dst, tmp);
}

int say(long number, char **buffer) {
    *buffer = strdup("zero");
    if(number == 0) return 0;
    else if(number < 0 || 999999999999 < number) return -1;

    *buffer = calloc(sizeof(char), MAX_LEN);
    for(int p = 0; number > 0; number /= 1000, p++) {
        char *res = thousands(number % 1000);
        if(strlen(res) > 0) {
            strcat(res, powers[p]);
            if(strlen(*buffer) > 0)
                strcat(res, " ");
            strpre(*buffer, res);
        }
    }
    return 0;
}
