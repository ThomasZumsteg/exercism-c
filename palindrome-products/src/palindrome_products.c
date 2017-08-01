#include "palindrome_products.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS (128)

int is_palindrome(char *str) {
    for(char *s = str, *e = s + strlen(str) - 1; s < e; s++, e--)
        if(*s != *e) return 0;
    return 1;
}

Pair getPalindromeProduct(int small, int large) {
    Pair *p = NULL;
    char num[MAX_DIGITS];
    int product;

    for(int i = small; i <= large; i++) {
        for(int j = i; j <= large; j++) {
            product = i * j;
            sprintf(num, "%d", product);
            if(is_palindrome(num)) {
                if(p == NULL){
                    p = malloc(sizeof(Pair));
                    p->small_palind = product;
                    p->larg_palind = product;
                } else if( product < p->small_palind)
                    p->small_palind = product;
                else if( p->larg_palind < product )
                    p->larg_palind = product;
            }
        }
    }
    return *p;
}
