#include "pangram.h"
#include <ctype.h>
#include <string.h>
#define LETTERS 26

int letter(char c) {
    if((c < 'a' || 'z' < c) && (c < 'A' || 'Z' < c)) return -1;
    return tolower(c) - 'a';
}

int is_pangram(const char *words) {
    if( words == NULL ) return 0;
    int letters[LETTERS] = { 0 };
    int l;
    for(const char *p = words; *p; p++) {
        if((l = letter(*p)) < 0) continue;
        letters[l]++;
    }
    for(int i = 0; i < LETTERS; i++) {
        if(letters[i] <= 0) return 0;
    }
    return 1;
}
