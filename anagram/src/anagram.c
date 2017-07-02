#include "anagram.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int comp(const void* element_1, const void* element_2) {
    char letter_1 = *((char *)element_1);
    char letter_2 = *((char *)element_2);
    return letter_1  - letter_2;
}

char *lower(const char word[MAX_STR_LEN]) {
    char *word_lower = malloc(sizeof(char) * MAX_STR_LEN);
    strcpy(word_lower, word);
    for( int i = 0; i < (int)strlen(word); i++)
        word_lower[i] = tolower(word[i]);
    return word_lower;
}

char *letters(const char word[MAX_STR_LEN]) {
    char *letters = malloc(sizeof(char) * MAX_STR_LEN);
    strcpy(letters, lower(word));
    qsort(letters, strlen(letters), sizeof(char), comp);
    return letters;
}

int is_anagram(const char *word1, const char *word2) {
    if(!strcmp(lower(word1), lower(word2)))
        return 0;
    return !strcmp(letters(word1), letters(word2));
}

struct Vector anagrams_for(char *anagram, struct Vector words) {
    struct Vector matches = {
        malloc(sizeof(char *) * words.size),
        0
    };
    for(int i = 0; i < words.size; i++) {
        if( is_anagram( words.vec[i], anagram )) {
            strcpy(matches.vec[matches.size++], words.vec[i]);
        }
    }
    return matches;
}
