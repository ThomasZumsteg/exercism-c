#include "sieve.h"
#include <stdlib.h>

unsigned int sieve(const unsigned int limit, primesArray_t primes) {
    char *sieve = calloc(limit + 1, sizeof(char));
    unsigned int n_primes = 0;
    for(int i = 2; i <= (int)limit; i++) {
        if(sieve[i] == 0) {
            primes[n_primes++] = i;
            for(int p = i * i; p <= (int)limit; p += i)
                sieve[p] = 1;
        }
    }
    return n_primes;
}
