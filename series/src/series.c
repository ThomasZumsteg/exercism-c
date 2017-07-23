#include "series.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *substr(char *text, int len) {
    char *result = calloc(sizeof(char), len);
    for(int t = 0, r = 0; t < len; t++, r++) {
        if(text[t] == 0) return NULL;
        result[r] = text[t];
    }
    return result;
}

SeriesResults_t series(char *inputText, unsigned int substringLength) {
    int n_substrs = strlen(inputText)-substringLength+2;
    SeriesResults_t *result = malloc(sizeof(SeriesResults_t));
    result->substringCount = 0;
    result->substring = calloc(sizeof(char*), n_substrs);
    if(n_substrs <= 0 || substringLength == 0)
        return *result;
    char *substr_p;
    for(char *in_p = inputText; *in_p; in_p++) {
        if((substr_p = substr(in_p, substringLength)) != NULL) 
            result->substring[result->substringCount++] = substr_p;
        else
            break;
    }
    return *result;        
}
