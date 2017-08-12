#include "react.h"
#include <stdlib.h>
#include <stdio.h>
#define DEBUG(x) x
#define MAX_CALLBACKS 10

struct reactor {
};

struct cell {
    int value;
    struct callback_data *callbacks;
};

struct callback_data {
    int id;
    callback func;
    void *args;
    struct callback_data *next;
};

struct compute_data {
    void *func;
    int n_args;
    struct cell **input;
    struct cell *output;
};

struct reactor *create_reactor() {
    struct reactor *r = malloc(sizeof(struct reactor));
    DEBUG(printf("Creating reactor %p\n", (void *)r));
    return r;
}

struct cell *create_input_cell(struct reactor *r, int initial_value) {
    struct cell *c = malloc(sizeof(struct cell));
    DEBUG(printf("Creating input cell %p\n", (void *)c));
    set_cell_value(c, initial_value);
    return c;
}

void compute_callback(void *data, int value) {
    struct compute_data *d = (struct compute_data *)data;
    switch(d->n_args) {
        case 0: return;
        case 1:
            set_cell_value(d->output, ((compute1)d->func)(
                        get_cell_value(d->input[0])));
            return;
        case 2:
            set_cell_value(d->output, ((compute2)d->func)(
                    get_cell_value(d->input[0]),
                    get_cell_value(d->input[1])));
            return;
        default:
            return;
    }
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *input,
        compute1 func) {
    struct cell *c = create_input_cell(r, func(get_cell_value(input)));
    DEBUG(printf("Creating compute1 cell %p\n", (void *)c));
    struct cell **input_array = calloc(sizeof(struct cell *), 1);
    input_array[0] = input;
    struct compute_data compute_data = { .output= c, .func = (void *)func,
        .n_args = 1, .input = input_array };
    add_callback(input, &c, compute_callback);
    return c;
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *input1,
        struct cell *input2, compute2 func) {
    struct cell *c = create_input_cell(r, func(get_cell_value(input1),
                get_cell_value(input2)));
    DEBUG(printf("Creating compute1 cell %p\n", (void *)c));
    add_callback(input1, c, compute_callback);
    add_callback(input2, c, compute_callback);
    return c;
}

int get_cell_value(struct cell *c) {
    DEBUG(printf("Getting cell value %p\n", (void *)c));
    return c->value;
}

void set_cell_value(struct cell *c, int new_value) {
    DEBUG(printf("Setting cell value %p\n", (void *)c));
    if(c->value == new_value)
        return;
    c->value = new_value;
    for(struct callback_data *data = c->callbacks; data != NULL; data = data->next)
        data->func(data->args, new_value);
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
