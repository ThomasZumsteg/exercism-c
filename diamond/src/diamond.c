#include <stdlib.h>
#include <stdio.h>
#include "diamond.h"

char **make_diamond(char letter) {
    int size = letter - 'A';
    char **result = calloc(sizeof(char *), 2*size+1);
    for(int l = 0; l <= 2*size; l++) {
        result[l] = calloc(sizeof(char), 2*size+1);
        for(int n = 0; n <= 2*size; n++) {
            int diff = size - abs(l - size);
            int pos = abs(l - size) + abs(n - size);
            result[l][n] = pos == size ? 'A' + diff : ' ';
        }
    }
    return result;
}
