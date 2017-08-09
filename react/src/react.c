#include "react.h"
#include <stdlib.h>
#include <stdio.h>
#define DEBUG(x) x
#define MAX_CALLBACKS 10

struct call {
    int id;
    void *args;
    callback callback;
    struct call *next;
};

struct reactor {
    struct call *first;
    struct call *last;
    int max_call_id;
};

struct cell {
    int value;
    struct reactor *reactor;
    void (*update)(struct cell *);
    struct cell **inputs;
    void *func;
    int n_inputs;
};

struct reactor *create_reactor() {
    return calloc(sizeof(struct reactor), 1);
}

struct cell *create_input_cell(struct reactor *r, int initial_value) {
    struct cell *c = calloc(sizeof(struct cell), 1);
    c->reactor = r;
    DEBUG(printf("Created cell %p\n", (void *)c));
    set_cell_value(c, initial_value);
    return c;
}

void compute1_callback(void *data, int id) {
    DEBUG(printf("Updating compute1 cell: %d\n", id));
    struct cell *cell = (struct cell *)data;
    compute1 func = (int (*)(int))cell->func;
    int input = get_cell_value(cell->inputs[0]);
    set_cell_value(cell, func(input));
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *input,
        compute1 func) {
    struct cell *cell = calloc(sizeof(struct cell),1);
    cell->func = (void *)func;
    cell->reactor = r;

    cell->inputs = calloc(sizeof(struct cell *), 1);
    cell->inputs[0] = input;

    add_callback(cell, (void *)cell, compute1_callback);

    return cell;
}

void compute2_callback(void *data, int id) {
    DEBUG(printf("Updating compute1 cell: %d\n", id));
    struct cell *cell = (struct cell *)data;
    compute2 func = (int (*)(int, int))cell->func;
    int input1 = get_cell_value(cell->inputs[0]);
    int input2 = get_cell_value(cell->inputs[1]);
    set_cell_value(cell, func(input1, input2));
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *input1,
        struct cell *input2, compute2 func) {
    struct cell *cell = calloc(sizeof(struct cell), 1);
    cell->reactor = r;
    cell->func = (void *)func;

    cell->inputs = calloc(sizeof(struct cell *), 2);
    cell->inputs[0] = input1;
    cell->inputs[1] = input2;

    add_callback(cell, (void *)cell, compute2_callback);
    return cell;
}

int get_cell_value(struct cell *c) {
    DEBUG(printf("Getting cell value %p\n", (void *)c));
    return c->value;
}

void set_cell_value(struct cell *c, int new_value) {
    DEBUG(printf("Setting cell value %p\n", (void *)c));
    struct reactor *r = c->reactor;
    c->value = new_value;
    for(struct call *d = r->first; d != NULL; d = d->next) {
        if(d->id == (int)c) {
            DEBUG(printf("Callback on %p\n", (void *)c));
            d->callback(d->args, d->id);
        }
    }
}

void destroy_reactor(struct reactor *r) {
    free(r);
}

callback_id add_callback(struct cell *c, void *args, callback func) {
    struct call *call = malloc(sizeof(call));
    call->id = (int)c;
    call->callback = func;
    call->args = args; 
    if(c->reactor->first == NULL) {
        c->reactor->first = call;
        c->reactor->last = call;
    } else {
        c->reactor->last->next = call;
        c->reactor->last = call;
    }
    return call->id;
}

void remove_callback(struct cell *c, callback_id id) {
    if(c && id) {}
}
