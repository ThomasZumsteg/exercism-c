#include "wordy.h"
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    START,
    NUMBER,
    OPERATOR,
} t_state;

typedef enum {
    PLUS,
    MINUS,
    MULT,
    DIV,
} t_operation;

const char *matchStart(const char *start) {
    static char *opening = "What is ";
    for(unsigned long c = 0; c < strlen(opening); c++) {
        if(start[c] != opening[c])
            return NULL;
    }
    return start + strlen(opening);
}

const char *readNumber(int *result, const char *input) {
    bool negative = false;
    const char *c = input;
    for( ; (c == input && *c == '-') || ('0' <= *c && *c <= '9'); c++) {
        if(*c == '-')
            negative = true;
        else
            *result = *result * 10 + (*c - '0');
    }
    *result *= negative ? -1 : 1;
    return c > input ? c : NULL;
}

const char *readOperator(t_operation *result, const char *input) {
    if(0 == strncmp(input, "plus", strlen("plus"))) {
        *result = PLUS;
        return input + strlen("plus") + 1;
    } else if(0 == strncmp(input, "minus", strlen("minus"))) {
        *result = MINUS;
        return input + strlen("minus") + 1;
    } else if(0 == strncmp(input, "multiplied by", strlen("multiplied by"))) {
        *result = MULT;
        return input + strlen("multiplied by") + 1;
    } else if(0 == strncmp(input, "divided by", strlen("divided by"))) {
        *result = DIV;
        return input + strlen("divided by") + 1;
    }
    return NULL;
}

bool answer(const char *question, int *result) {
    t_state state = START;
    t_operation operation = PLUS;
    *result = 0;
    const char *c = question;
    int *buffer;
   
    while(*c) {
        switch(state) {
            case START:
                if((c = matchStart(c)) == NULL)
                    return false;
                state = NUMBER;
                operation = PLUS;
                break;
            case NUMBER:
                buffer = calloc(sizeof(int), 1);
                if((c = readNumber(buffer, c)) == NULL)
                    return false;
                c++;
                switch(operation) {
                    case PLUS:
                        *result += *buffer;
                        break;
                    case MINUS:
                        *result -= *buffer;
                        break;
                    case MULT:
                        *result *= *buffer;
                        break;
                    case DIV:
                        *result /= *buffer;
                        break;
                }
                if(*c != '?')
                    state = OPERATOR;
                break;
            case OPERATOR:
                if((c = readOperator(&operation, c))== NULL)
                    return false;
                state = NUMBER;
                break;
        }
    }
    return true;
}
