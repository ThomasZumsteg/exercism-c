#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "isogram.h"

int cmp(const void *e1, const void *e2) {
    return *(char*)e1 - *(char*)e2;
}

int isIsogram(char *word) {
    char *letters = malloc(sizeof(char) * strlen(word));
    for(int i = 0; i < (int)strlen(word); i++)
        letters[i] = tolower(word[i]);
    qsort(letters, strlen(letters), sizeof(char), cmp);
    for(int i = 1; i < (int)strlen(word); i++) {
        if( letters[i] < 'a' ) 
            continue;
        else if( letters[i] > 'z' )
            break;
        else if( letters[i] == letters[i - 1])
            return 0;
    }
    return 1;
}
