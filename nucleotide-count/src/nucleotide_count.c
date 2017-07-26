#include "nucleotide_count.h"
#include <stdio.h>
#include <stdlib.h>

struct DNA_count { unsigned int G, T, A, C; };

int inc_dna_count(struct DNA_count *cnt, char nuc) {
    switch(nuc) {
        case 'G': cnt->G++; break;
        case 'T': cnt->T++; break;
        case 'A': cnt->A++; break;
        case 'C': cnt->C++; break;
        default: return -1; // Uknown nucleiotide
    }
    return 0;
}


char *count(const char *dna) {
    struct DNA_count counter = { .G = 0, .C = 0, .A = 0, .T = 0};
    char *result = calloc(sizeof(char), 25);
    for(const char *c = dna; *c; c++) {
        if(inc_dna_count(&counter, *c) != 0)
            return result;
    }
    sprintf(result, "A:%d C:%d G:%d T:%d", counter.A, counter.C, counter.G,
            counter.T);
    return result;
}
