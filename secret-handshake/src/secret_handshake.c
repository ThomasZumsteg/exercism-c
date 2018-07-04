#include <stdlib.h>
#include "secret_handshake.h"

#define STEPS 4

const char *steps[STEPS] = { "wink", "double blink", "close your eyes", "jump" };

void swap(const char **a, const char **b) {
    const char *tmp = *a;
    *a = *b;
    *b = tmp;
}

const char **commands(int signal) {
    const char **results = calloc(sizeof(char **), 1);
    const char **result = results;
    for(int word = 0; word < STEPS; word++) {
        if((1<<word)&signal)
            *(result++) = steps[word];
    }
    if((1<<STEPS)&signal) {
        result--;
        for(const char **r = results; r < result; r++, result--)
            swap(r, result);
    }
    return results;
}
