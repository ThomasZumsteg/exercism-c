#include "beer_song.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE   (1024)

void verse(char *buff, int v) {
    switch(v) {
        case 0:
            sprintf(buff, "No more bottles of beer on the wall, "
                "no more bottles of beer.\n"
                "Go to the store and buy some more, "
                "99 bottles of beer on the wall.\n");
            break;
        case 1:
            sprintf(buff, "1 bottle of beer on the wall, "
                "1 bottle of beer.\n" 
                "Take it down and pass it around, "
                "no more bottles of beer on the wall.\n");
            break;
        case 2:
            sprintf(buff, "2 bottles of beer on the wall, "
                "2 bottles of beer.\n" 
                "Take one down and pass it around, "
                "1 bottle of beer on the wall.\n");
            break;
        default:
            sprintf(buff, "%d bottles of beer on the wall, %d bottles of beer.\n" 
                "Take one down and pass it around, "
                "%d bottles of beer on the wall.\n", v, v, v-1);
    }
}

void sing(char *buff, int start, int stop) {
    char verse_buff[BUFFER_SIZE];
    memset(buff, 0, BUFFER_SIZE);
    for(int v = start; v >= stop; v--) {
        verse(verse_buff, v);
        strcat(buff, verse_buff);
        strcat(buff, "\n");
    }
    buff[strlen(buff) - 1] = '\0';
}
