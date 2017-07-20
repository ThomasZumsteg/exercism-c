#include "atbash_cipher.h"
#include <string.h>
#include <stdlib.h>

char swap_char(char c) { 
    if('a' <= c && c <= 'z') 
        return 'a' + 'z' - c;
    else if('A' <= c && c <= 'Z')
        return  'A' + 'z' - c;
    else if('0' <= c && c <= '9')
        return c;
    return 0;
}

char *atbash_encode(char *plaintext) {
    char *ciphertext = malloc(sizeof(char) * strlen(plaintext));
    int i = 0;
    char p;
    for(char *c = plaintext; *c; c++) {
        if((p = swap_char(*c)) != 0)
            ciphertext[i++] = p;
        if(i % 6 == 5)
            ciphertext[i++] = ' ';
    }
    if(ciphertext[i-1] == ' ')
        ciphertext[i-1] = 0;
    else
        ciphertext[i] = 0;
    return ciphertext;
}

char *atbash_decode(char *ciphertext) {
    char *plaintext = malloc(sizeof(char) * strlen(ciphertext));
    char p;
    int i = 0;
    for(char *c = ciphertext; *c; c++) {
        if((p = swap_char(*c)) != 0)
            plaintext[i++] = p;
    }
    plaintext[i] = 0;
    return plaintext;
}
