#include "rna_transcription.h"
#include <stdlib.h>
#include <string.h>

char char_to_rna(char dna) {
    switch(dna) {
        case 'G': return 'C';
        case 'T': return 'A';
        case 'A': return 'U';
        case 'C': return 'G';
        default: return 0;
    }
}

char *to_rna(const char *dna) {
    char *rna = malloc(sizeof(char) * strlen(dna));
    char *r;
    const char *d;
    for(r = rna, d = dna; *d; d++, r++) {
        *r = char_to_rna(*d);
        if(*r == 0) return 0;
    }
    return rna;
}
