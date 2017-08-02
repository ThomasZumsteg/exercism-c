#include "scrabble_score.h"
#include <ctype.h>
#include <string.h>

int letter_val(char c) {
    if(strchr("AEIOULNRST", c) != 0)
       return 1;
   else if(strchr("DG", c) != 0)
       return 2;
    else if(strchr("BCMP", c) != 0)
        return 3;
    else if(strchr("FHVWY", c) != 0)
        return 4;
    else if(strchr("K", c) != 0)
        return 5;
    else if(strchr("JX", c) != 0)
        return 8;
    else if(strchr("QZ", c) != 0)
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
