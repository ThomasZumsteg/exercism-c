#include "crypto_square.h"
#include <strings.h>
#include <stdlib.h>
#include <math.h>

char *clean(const char *text) {
    char *result = calloc(sizeof(char), strlen(text));
    char *p_result = result;
    for(const char *c = text; *c; c++) {
        char tmp = *c;
        if('A' <= tmp && tmp <= 'Z')
            tmp += 'a' - 'A';
        if(('a' <= tmp && tmp <= 'z') || ('0' <= tmp && tmp <= '9')) {
            *p_result = tmp;
            p_result++;
        }
    }
    return result;
}

char *ciphertext(const char *plaintext) {
    char *cleaned = clean(plaintext);
    char *c = clean(plaintext);
    int rows = ceil(sqrt(strlen(cleaned)));
    if(rows == 0)
        return cleaned;
    int cols = ceil(strlen(cleaned) / (float)rows) + 1;
    char *result = calloc(sizeof(char), rows*cols);
    for(int col = 0; col < cols; col++) {
        for(int row = 0; row < rows; row++) {
            result[row*cols+col] = *c ? *(c++) : ' ';
        }
    }
    result[rows*cols-1] = '\0';
    return result;
}
