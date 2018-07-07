#include "run_length_encoding.h"
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

#define MAX_LEN 255

char *encode(char *input) {
    char *result = calloc(sizeof(char), MAX_LEN);
    char prev;
    int count = 0;
    for(char *c = input; *c; c++) {
        if(prev == *c)
            count++;
        else {
            if(count > 1)
                sprintf(result, "%s%d%c", result, count, prev);
            else
                sprintf(result, "%s%c", result, prev);
            count = 1;
            prev = *c;
        }
    }
    if(count > 1)
        sprintf(result, "%s%d%c", result, count, prev);
    else
        sprintf(result, "%s%c", result, prev);
    return result;
}

char *decode(char *input) {
    char *result = calloc(sizeof(char), MAX_LEN);
    char *p_result = result;
    int count = 0;
    for(char *c = input; *c; c++) {
        if('0' <= *c && *c <= '9') {
            count *= 10;
            count += (int)(*c - '0');
        } else {
            for(int i = count > 0 ? count : 1; 0 < i; i--)
                *(p_result++) = *c;
            count = 0;
        }
    }
    return result;
}
