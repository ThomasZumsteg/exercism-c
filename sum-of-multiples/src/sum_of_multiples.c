#include "sum_of_multiples.h"

int sum_of_multiples(const unsigned int *multiples, size_t len, unsigned int num) {
    unsigned int total = 0;
    for(unsigned int n = 1; n < num; n++) {
        for(size_t i = 0; i < len; i++) {
            if(0 == n % multiples[i]) {
                total += n;
                break;
            }
        }
    }
    return total;
}
