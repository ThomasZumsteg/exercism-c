#include "grains.h"

unsigned long square(int n) {
    if( n < 1 || 64 < n ) return 0;
    unsigned long total = 1;
    for(int i = 1; i < n; i++)
        total *= 2;
    return total;
}

unsigned long total() {
    return 18446744073709551615ul;
}
