#include "two_fer.h"
#include "stdio.h"

void two_fer(char *buffer, char *name) {
    sprintf(buffer, "One for %s, one for me.", name != NULL ? name : "you"); 
}

