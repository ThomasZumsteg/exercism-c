#include "bracket_push.h"
#include <strings.h>

#define MAX_STACK 10

int is_paired(const char *string) {
    static char *brackets = "[]{}()";
    char stack[MAX_STACK];
    char *stack_p = stack;
    for(const char *c = string; *c; c++) {
        char *bracket = strchr(brackets, *c);
        if(bracket) {
            if((bracket - brackets) % 2 == 0)
                *(stack_p++) = *c;
            else if(*(--stack_p) != *(bracket-1))
                return 0;
        }
    }
    return stack_p == stack;
}

