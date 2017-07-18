#include "word_count.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *nstrtok(char *text, int (*test)(char, char*)) {
    static char *text_p;
    char *buff = calloc(sizeof(char) * MAX_WORD_LENGTH, 0);
    char *buff_p;

    if(text != NULL) text_p = text;

    while(*text_p && !test(*text_p, text_p)) text_p++;
    for(buff_p = buff; *text_p && test(*text_p, text_p); text_p++, buff_p++)
        *buff_p = *text_p;
    return buff_p == buff ? NULL : buff;
}

int ok_char(char c, char *char_p) {
    if(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) return 1;
    else if('0' <= c && c <= '9') return 1;
    else if(c == '\'' && ok_char(*(char_p+1), NULL) && ok_char(*(char_p - 1), NULL))
        return 1;
    return 0;
}

void lower(char *word) { for(char *p = word; *p; p++) *p = tolower(*p); }

int word_count(char *input_text, WordCount_Word_t words[MAX_WORDS]) {
    int i, nWords = 0;
    for(char *word = nstrtok(input_text, ok_char);
            word != NULL;
            word = nstrtok(NULL, ok_char)) {
        lower(word);
        for(i = 0; i < nWords; i++) {
            if(strcmp(words[i].text, word) == 0) {
                words[i].count++;
                break;
            }
        }
        if(nWords <= i) {
            strcpy(words[nWords].text, word);
            words[nWords].count = 1;
            nWords++;
        }
    }
    return nWords;
}
