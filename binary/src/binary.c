#include "binary.h"

int convert(char *digits) {
    int total = 0;
    for(char *d = digits; *d; d++) {
        total *= 2;
        if(*d == '1') total += 1;
        else if(*d != '0') return INVALID;
    }
    return total;
}
