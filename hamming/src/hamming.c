#include "hamming.h"
#include <string.h>

int compute(char* dna_a, char* dna_b) {
    int chars = strlen(dna_a) < strlen(dna_b) ? strlen(dna_a) : strlen(dna_b);
    int diffs = 0;
    for(int i = 0; i < chars; i++) {
        if(dna_a[i] != dna_b[i])
            diffs++;
    }
    return diffs;
}
