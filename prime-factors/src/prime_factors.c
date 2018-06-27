# include "prime_factors.h"

size_t find_factors(uint64_t base, uint64_t factors[]) {
    uint64_t divisor = 2;
    size_t f = 0;
    while(base > 1) {
        if(base % divisor == 0) {
            factors[f++] = divisor;
            base /= divisor;
        } else 
            divisor += divisor == 2 ? 1 : 2;
    }
    return f;
}
