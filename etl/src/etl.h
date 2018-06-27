#include <stdlib.h>

typedef struct {
    char key;
    int value;
} new_map;

typedef struct {
    int key;
    char *value;
} legacy_map;

int convert(legacy_map *input, int items, new_map **output);
