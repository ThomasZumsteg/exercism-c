#include "roman_numerals.h"
#include <string.h>
#include <stdlib.h>

#define NUM_ROMAN_DIGITS 13

struct RomanNumeral{
    int arabic;
    char *greek;
};

const struct RomanNumeral ROMANDIGITS[NUM_ROMAN_DIGITS] = {
    {    1, "I" }, {    4, "IV" }, {    5, "V" }, {    9, "IX" },
    {   10, "X" }, {   40, "XL" }, {   50, "L" }, {   90, "XC" },
    {  100, "C" }, {  400, "CD" }, {  500, "D" }, {  900, "CM" },
    { 1000, "M" }
};

char *to_roman_numeral(int arabic) {
    char *greek = calloc(sizeof(char) * 64, 0);
    for(const struct RomanNumeral *n = ROMANDIGITS + NUM_ROMAN_DIGITS - 1;
            ROMANDIGITS <= n; 
            n-- ) {
        for(int c = arabic / n->arabic; 0 < c; c--)
            strcat(greek, n->greek);
        arabic = arabic % n->arabic;
    }
    return greek; 
}
