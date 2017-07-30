#include "perfect_numbers.h"
#include <stdlib.h>

int factor_sum(int num) {
    int n, total = 1;
    for(n = 2; n * n < num; n++ ) {
        if( num % n != 0) continue;
        total += n + (num / n);
    }
    if( n * n == num ) total += n;
    return total;
}   


kind classify_number(int num) {
    int sum = factor_sum(num);

    if(num < 1) return error;
    else if(num == 1 || num > sum) return deficient_number;
    else if(num < sum) return abundant_number;
    else return perfect_number;
}
