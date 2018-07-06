#include "minesweeper.h"
#include <strings.h>
#include <stdlib.h>

typedef struct {
    size_t row;
    size_t col;
} tTuple;

char count(const char **field, tTuple square, tTuple size) {
    tTuple diffs[] = {
        { 1,  1}, { 1,  0}, { 1, -1},
        { 0,  1},           { 0, -1},
        {-1,  1}, {-1,  0}, {-1, -1} };
    int mines = 0;
    for(int d = 0; d < 8; d++) {
        size_t r = square.row+diffs[d].row;
        size_t c = square.col+diffs[d].col;
        if(r < size.row && c < size.col && field[r][c] == '*')
            mines++;
    }
    return mines > 0 ? '0' + mines : field[square.row][square.col];
}

char **annotate(const char **field, size_t rows) {
    if(field == NULL)
        return NULL;
    char **result = calloc(sizeof(char *), rows + 1);
    tTuple size = {rows, strlen(field[0])};
    for(size_t row = 0; row < size.row; row++) {
        *(result+row) = calloc(sizeof(char), rows + 1);
        for(size_t col = 0; col < size.col; col++) {
            tTuple square = {row, col};
            if(field[row][col] == ' ')
                result[row][col] = count(field, square, size);
            else
                result[row][col] = field[row][col];
        }
        result[row][size.col] = '\0';
    }
    return result;
}

void free_annotation(char **field) {
    free(field);
}
