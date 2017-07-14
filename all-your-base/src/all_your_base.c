#include "all_your_base.h"
#include <stdio.h>

unsigned long int from_base(int8_t *digits, int base, size_t len) {
    unsigned long int result = 0;
    for(int8_t *d = digits; d - digits < (long)len; d++) {
        if(*d < 0 || base <= *d) return 0;
        result = base * result + *d;
    }
    return result;
}

size_t to_base(unsigned long int num, int base, int8_t *result) {
    int8_t digits[DIGITS_ARRAY_SIZE];
    size_t i;
    for(i = 0; num > 0; num /= base, i++)
        digits[i] = num % base;
    for(int j = i, k = 0; 0 <= j; j--, k++)
        result[k] = digits[j-1];
    return i;
}

size_t rebase(int8_t *digits, int8_t f_base, int8_t t_base, size_t len) {
    if(digits[0] == 0 || f_base <= 1 || t_base <= 1) return 0;
    unsigned long int num = from_base(digits, f_base, len);
    return to_base(num, t_base, digits);
}
