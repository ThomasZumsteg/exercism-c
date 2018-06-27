#include "etl.h"
#include <stdio.h>

int convert(legacy_map *input, int legacy_items, new_map **output) {
    *output = (new_map *)malloc(sizeof(output));
    int new_items = 0;
    for(int i = 0; i < legacy_items; i++) {
        for(char *c = input[i].value; *c; c++) {
            output[new_items] = (new_map *)malloc(sizeof(new_map));
            output[new_items]->key = (*c - 'A') + 'a';
            output[new_items]->value = input[i].key;
            new_items++;
        }
    }
    return new_items;
}
