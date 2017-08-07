#include "react.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX_CALLBACKS 10

struct reactor {
    void (*update)(struct reactor *);
    void *func;
    struct cell **inputs;
    int n_inputs;
    struct cell *output;
};

struct cell {
    int value;
    struct reactor *reactor;
};

struct reactor *create_reactor() {
    return calloc(sizeof(struct reactor), 1);
}

struct cell *create_input_cell(struct reactor *r, int initial_value) {
    struct cell *c = calloc(sizeof(struct cell), 1);
    c->reactor = r;
    set_cell_value(c, initial_value);
    return c;
}

void update_compute1(struct reactor *reactor) {
    struct cell *output = reactor->output;
    compute1 func = (int (*)(int))reactor->func;
    int input = get_cell_value(reactor->inputs[0]);
    set_cell_value(output, func(input));
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *input,
        compute1 func) {
    r->output = create_input_cell(r, func(input->value));
    r->func = (void *)func;
    r->inputs = &input;
    r->update = &update_compute1;
    return r->output;
}

void update_compute2(struct reactor *reactor) {
    struct cell *output = reactor->output;
    compute2 func = (int (*)(int, int))reactor->func;
    int input1 = get_cell_value(reactor->inputs[0]);
    int input2 = get_cell_value(reactor->inputs[1]);
    set_cell_value(output, func(input1, input2));
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *input1,
        struct cell *input2, compute2 func) {
    r->output = create_input_cell(r, func(input1->value, input2->value));
    r->func = (void *)func;
    r->inputs = calloc(sizeof(struct cell), 2);
    r->inputs[0] = input1;
    r->inputs[1] = input2;
    return r->output;
}

int get_cell_value(struct cell *c) {
    return c->value;
}

void set_cell_value(struct cell *c, int new_value) {
    c->value = new_value;
    if(c->reactor->update != NULL) {
        c->reactor->update(c->reactor);
    }
}

void destroy_reactor(struct reactor *r) {
    free(r);
}

callback_id add_callback(struct cell *c, void *args, callback func) {
    if(c && args && func) {}
    return 0;
}

void remove_callback(struct cell *c, callback_id id) {
    if(c && id) {}
}
