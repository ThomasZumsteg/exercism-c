#include "react.h"
#include <stdlib.h>

typedef int (*func)();

struct reactor {
    func func;
    int n_inputs;
    struct cell **inputs;
};

struct cell {
    int value;
    struct reactor *update;
};

struct reactor *create_reactor() {
    return malloc(sizeof(struct reactor));
}

struct cell *create_input_cell(struct reactor *r, int initial_value) {
    struct cell *c = malloc(sizeof(struct cell));
    c->value = initial_value;
    return c;
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *input,
        compute1 func) {
    r->func = func; 
    r->n_inputs = 1;
    r->inputs[0] = input;
    struct cell *c = malloc(sizeof(struct cell));
    return c;
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *input1,
                                  struct cell *input2, compute2 func) {
    r->func = func; 
    r->n_inputs = 2;
    r->inputs[0] = input1;
    r->inputs[1] = input2;
    struct cell *c = malloc(sizeof(struct cell));
    return c;
}

int get_cell_value(struct cell *c) {
    return c->value;
}

void set_cell_value(struct cell *c, int new_value) {
    c->value = new_value;
}

void destroy_reactor(struct reactor *r) {
    free(r);
}

callback_id add_callback(struct cell *, void *, callback) {
}

void remove_callback(struct cell *, callback_id) {
}
