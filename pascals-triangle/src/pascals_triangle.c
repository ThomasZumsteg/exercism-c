#include "pascals_triangle.h"
#include <stdlib.h>
#include <stdio.h>

size_t **create_triangle(size_t size) {
    if((int)size < 0) return NULL;
    size_t **triangle = calloc(sizeof(size_t *), size);
    if(size == 0) {
        triangle[0] = calloc(sizeof(size_t), 1);
        return triangle;
    }
    for(size_t i = 0, *row; i < size; i++) {
        row = calloc(sizeof(size_t), size);
        row[0] = 1;
        for(size_t j = 1; j <= i; j++)
            row[j] = triangle[i-1][j] + triangle[i-1][j-1];
        triangle[i] = row;
    }

    return triangle;
}

void free_triangle(size_t **triangle, size_t size) {
    for(size_t i = 0; i < size; i++)
        free(triangle[i]);
    free(triangle);
}

