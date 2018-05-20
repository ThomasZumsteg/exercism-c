#include "scrabble_score.h"
#include <ctype.h>
#include <string.h>

int letter_val(char c) {
    if(strchr("AEIOULNRST", c))
       return 1;
   else if(strchr("DG", c))
       return 2;
    else if(strchr("BCMP", c))
        return 3;
    else if(strchr("FHVWY", c))
        return 4;
    else if(strchr("K", c))
        return 5;
    else if(strchr("JX", c))
        return 8;
    else if(strchr("QZ", c))
        return 10;
    return -1;
}

int score(char *word) {
    int val, total = 0;
    for(char *c = word; *c; c++) {
        if((val = letter_val(toupper(*c))) >= 0)
            total += val;
    }
    return total;
}
