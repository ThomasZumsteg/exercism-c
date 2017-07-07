#include "bob.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void chomp(char *str) {
    for(char *p = strlen(str) + str - 1; str <= p && *p == ' '; p--) {
        *p = '\0';
    }
}


int count(char *str, int (*test)(char)) {
    int count = 0;
    for(int i = 0; str[i]; i++) { if(test(str[i])) count++; }
    return count;
}

int upper(char c) { return 'A' <= c && c <= 'Z'; }
int lower(char c) { return 'a' <= c && c <= 'z'; }
char last_char(char *str) { return str[strlen(str) - 1]; }

char *hey_bob(char *str) {
    char *greeting = malloc(sizeof(char) * strlen(str));
    strcpy(greeting, str);
    chomp(greeting);
    if(strcmp(greeting, "") == 0) return "Fine. Be that way!";
    else if(count(greeting, &lower) == 0 && count(greeting, &upper) > 1)
        return "Whoa, chill out!";
    else if(last_char(greeting) == '?') return "Sure.";
    return "Whatever.";
}
