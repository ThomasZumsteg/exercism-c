#include "luhn.h"
#include <strings.h>

int luhn(char *code) {
    int len = 0;
    int total = 0;
    for(int c = (int)strlen(code) - 1; 0 <= c; c--) {
        if('0' <= code[c] && code[c] <= '9') {
            int digit = (int)(code[c] - '0');
            total += digit;
            if(len % 2 == 1)
                total += digit - (5 <= digit ? 9 : 0);
            len++;
        } else if(code[c] != ' ')
            return 0;
    }
    return 1 < len && (total % 10 == 0);
}
