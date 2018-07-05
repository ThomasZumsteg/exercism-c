#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "pig_latin.h"

#define MAX_LEN 256

const char *vowel(const char *word) {
    for(const char *c = word; *c; c++) {
        switch(*c) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
                return c;
            case 'u':
                if(c == word || *(c-1) != 'q')
                    return c;
                break;
            case 'y':
                if(!(*(c+1) && strchr("aeiou", *(c+1))))
                    return c;
                break;
        }
    }
    return 0;
}

char *translate_word(const char *input) {
    char *result = calloc(sizeof(char), MAX_LEN);
    const char *split = vowel(input);
    strcpy(result, split);
    strncat(result, input, split - input);
    if(0 < strcmp(result + strlen(result), "a"))
        strcat(result, "y");
    else {
        if(!strcmp(split, "ay"))
            strcpy(result, input);
        strcat(result, "ay");
    }
    return result;
}

char *translate(const char *input) {
    char *result = calloc(sizeof(char), MAX_LEN);
    char *end = strchr(input, ' ');
    char *start = (char *)input;
    for(; end; end = strchr(end+1, ' ')) {
        char *tmp = calloc(sizeof(char), MAX_LEN);
        strncpy(tmp, start, end - start);
        if(start != input)
            strcat(result, " ");
        strcat(result, translate_word(tmp));
        start = end+1;
    }
    if(start != input)
        strcat(result, " ");
    strcat(result, translate_word(start));
    return result;
}


