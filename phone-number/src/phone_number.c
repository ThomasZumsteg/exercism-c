#include "phone_number.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define N_DIGITS 10

char get_digit(char c) {
    if('0' <= c && c <= '9')
        return c;
    else if(strchr(".()- ", c) != 0)
        return 0;
    else
        return -1;
}

void shift_str(char *s, int d) {
    char *sd;
    for(sd = s + d; *sd; sd++, s++)
        *s = *sd;
    *s = 0;
}

char *substr(const char *str, int start, int stop) {
    char *slice = malloc(sizeof(char) * strlen(str));
    strcpy(slice, str + start);
    slice[stop - start] = 0;
    return slice;
}
    

char *phone_number_clean(const char *number) {
    char *phone_number = calloc(N_DIGITS, 0);
    int p = 0;
    char n;
    for(const char *c = number; *c; c++) {
        n = get_digit(*c);
        if( n == -1) {
            strcpy(phone_number, "0000000000");
            break;
        } else if( n != 0 )
            phone_number[p++] = n;
    }
    if(strlen(phone_number) == 11 && *phone_number == '1')
        shift_str(phone_number, 1);
    if(strlen(phone_number) != 10)
        strcpy(phone_number, "0000000000");
    return phone_number;
}

char *phone_number_get_area_code(const char *number) {
    return substr(phone_number_clean(number), 0, 3);
}

char *phone_number_format(const char *number) {
    char *num = phone_number_clean(number);
    char *p_num = malloc(sizeof(char) * 14);
    sprintf(p_num, "(%s) %s-%s", substr(num, 0, 3), substr(num, 3, 6),
            substr(num, 6, 10));
    return p_num;
}
