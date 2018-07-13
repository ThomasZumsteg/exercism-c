#include "nth_prime.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

int n_primes;

int prime(uint32_t num, uint32_t primes[]) {
    for(uint32_t *n = primes; *n * *n <= num; n++ ) {
        if(num % *n == 0)
            return 0;
    }
    return 1;
}

uint32_t nth(int n) {
    if(n <= 0) return 0;
    uint32_t *primes = calloc(n, sizeof(uint32_t));
    n_primes = 2;
    primes[0] = 2;
    primes[1] = 3;
    for(uint32_t p = 5; n_primes < n; p+=2) {
        if(prime(p, primes))
            primes[n_primes++] = p;

    }
    uint32_t result = primes[n-1];
    free(primes);
    return result;
}

