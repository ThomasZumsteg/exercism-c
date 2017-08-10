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
    struct call *callbacks[MAX_CALLBACKS];
    int next_id;
};

struct cell {
    int value;
    struct reactor *reactor;
    callback_id callback_id;
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

struct compute1_data { compute1 func; struct cell *input; struct cell *output; };

void compute1_callback(void *data, int id) {
    if(id) {}
    struct compute1_data *state = (struct compute1_data *)data;
    DEBUG(printf("Updating compute1 cell: %p\n", (void *)state->output));
    set_cell_value(state->output, state->func(get_cell_value(state->input)));
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *input,
        compute1 func) {
    struct cell *cell = calloc(sizeof(struct cell),1);
    DEBUG(printf("Creating compute1 cell: %p\n", (void *)cell));
    cell->reactor = r;
    struct compute1_data data = { .func = func, .input = input, .output = cell };
    cell->callback_id = add_callback(cell, &data, compute1_callback);
    return cell;
}

struct compute2_data { compute2 func; struct cell *input1; struct cell *input2;
    struct cell *output; };

void compute2_callback(void *data, int id) {
    if(id) {}
    struct compute2_data *state = (struct compute2_data *)data;
    DEBUG(printf("Updating compute2 cell: %p\n", (void *)state->output));
    set_cell_value(state->output, state->func(
                get_cell_value(state->input1), get_cell_value(state->input2)));
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *input1,
        struct cell *input2, compute2 func) {
    struct cell *cell = calloc(sizeof(struct cell), 1);
    DEBUG(printf("Creating compute2 cell: %p\n", (void *)cell));
    cell->reactor = r;
    struct compute2_data data = { .func = func, .output = cell,
        .input1 = input1, .input2 = input2 };
    cell->callback_id = add_callback(cell, &data, compute2_callback);
    return cell;
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
    free(r);
}

callback_id add_callback(struct cell *c, void *args, callback func) {
    struct call *call = malloc(sizeof(call));
    call->id = c->reactor->next_id++;
    call->callback = func;
    call->args = args; 
    c->reactor->callbacks[call->id] = call;
    return call->id;
}

void remove_callback(struct cell *c, callback_id id) {
    if(c && id) {}
}
