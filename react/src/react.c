#include "react.h"
#include <stdlib.h>
#include <stdio.h>
#define DEBUG(x) x
#define CELL_ALLOC 10

struct reactor {
    struct cell **cells;
    int n_cells;
};

struct cell {
    int value;
};

struct reactor *create_reactor() {
    struct reactor *r = calloc(sizeof(struct reactor), 1);
    DEBUG(printf("Creating reactor %p\n", (void *)r));
    r->cells = calloc(sizeof(struct cell *), CELL_ALLOC);
    return r;
}

struct cell *create_input_cell(struct reactor *r, int initial_value) {
    struct cell *c = calloc(sizeof(struct cell), 1);
    DEBUG(printf("Creating input cell %p\n", (void *)c));
    r->cells[r->n_cells++] = c;
    set_cell_value(c, initial_value);
    return c;
}

void compute1_callback(void *data, int value) {
    struct cell *c = (struct cell *)data;
    set_cell_value(c, value);
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *input,
        compute1 func) {
    struct cell *c = create_input_cell(r, func(get_cell_value(input)));
    DEBUG(printf("Creating compute1 cell %p\n", (void *)c));
    add_callback(c, &c, compute1_callback);
    return c;
}

void compute2_callback(void *data, int value) {
    struct cell *c = (struct cell *)data;
    set_cell_value(c, value);
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *input1,
        struct cell *input2, compute2 func) {
    struct cell *c = create_input_cell(r, func(get_cell_value(input1),
                get_cell_value(input2)));
    DEBUG(printf("Creating compute1 cell %p\n", (void *)c));
    add_callback(c, &c, compute2_callback);
    return c;
}

int get_cell_value(struct cell *c) {
    DEBUG(printf("Getting cell value %p\n", (void *)c));
    return c->value;
}

void set_cell_value(struct cell *c, int new_value) {
    DEBUG(printf("Setting cell value %p\n", (void *)c));
    c->value = new_value;
}

void destroy_reactor(struct reactor *r) {
    for(int i = 0; i < r->n_cells; i++)
        free(r->cells[i]);
    free(r);
}

callback_id add_callback(struct cell *c, void *args, callback func) {
    if(c && args && func) {}
    return 0;
}

void remove_callback(struct cell *c, callback_id id) {
    if(c && id) {}
}
