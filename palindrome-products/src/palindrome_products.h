#ifndef PALINDROME_PRODUCTS_H
#define PALINDROME_PRODUCTS_H

typedef struct {
    int small_palind;
    int larg_palind;
} Pair;
 
Pair getPalindromeProduct(int small, int large);

#endif
