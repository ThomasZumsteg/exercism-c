#include "binary_search.h"
#include <stdio.h>

int *binary_search(int needle, int *haystack, size_t len) {
    for(int *start = haystack, *end = start + len - 1; 0 < len; len /= 2) {
        haystack = start + len / 2;
        if(*haystack > needle)
            end = haystack - 1;
        else if(*haystack < needle)
            start = haystack + 1;
        else
            return haystack;
    }
    return 0;
}
