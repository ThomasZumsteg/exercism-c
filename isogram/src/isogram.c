#include <ctype.h>
#include <string.h>
#include "isogram.h"

int isIsogram(char *word) {
    int word_length = strlen(word);
    char letter;
    for (int i = 0; i + 1 < word_length; i++) {
        letter = tolower(word[i]);
        if( letter < 'a' || 'z' < letter)
            continue;
        for (int j = i + 1; j < word_length; j++) 
            if(tolower(word[j]) == letter)
                return 0;
    }
    return 1;
}
