#include "acronym.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int breaking_char(char c) {
    return c == ' ' || c == '-';
}

char *abbreviate(char *phrase) {
    char *abbr = malloc(sizeof(char) * strlen(phrase));
    memset(abbr, 0, sizeof(char) * strlen(phrase));
    for(char *p = phrase, *q = abbr; *p; p++) {
        if(p == phrase || breaking_char(*(p-1)))
            *q++ = toupper(*p);
    }
    return abbr;
}
