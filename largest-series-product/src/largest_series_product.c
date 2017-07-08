#include "largest_series_product.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int ctoi(char c) {
    if(c < '0' || '9' < c) return -1;
    return c - '0';
}

long largest_series_product(char *digits, int len) {
    if(strcmp(digits, "") == 0) return len == 0 ? 1 : -1;
    long product, d, largest = 0;
    for(char *p = digits; *p; p++) {
      product = 1;
      for(int j = 0; j < len; j++) {
        if( !p[j] ) return p == digits ? -1 : largest; 
        if((d = ctoi(p[j])) < 0) return -1;
        product *= d;
      }
      largest = product < largest ? largest : product;
    }
    return largest;
}
