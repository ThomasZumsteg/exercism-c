#include "react.h"
#include <stdlib.h>
#include <stdio.h>
#define DEBUG(x)
#define MAX_CELLS 10

struct reactor {
    struct cell **cells;
    int n_cells;
};

struct cell {
    int value;
    void (*update)(struct cell *);
    struct reactor *reactor;
    void *func;
    struct cell **inputs;
    int n_inputs;
    callback_id ids;
    struct callback_data *callbacks;
};

struct reactor *create_reactor() {
    DEBUG(printf("Creating reactor\n"));
    struct reactor *r = malloc(sizeof(struct reactor));
    r->cells = calloc(sizeof(struct cell *), MAX_CELLS); 
    r->n_cells = 0;
    return r;
}

void update_reactor(struct reactor *r) {
    DEBUG(printf("Updating reactor\n"));
    for(int i = 0; i < r->n_cells; i++) {
        DEBUG(printf("Next %p\n", (void *)r->cells[i]));
        r->cells[i]->update(r->cells[i]);
    }
}

struct cell *create_cell(struct reactor *r, void update(struct cell *),
        void *func, int value) {
    struct cell *c = malloc(sizeof(struct cell));
    r->cells[r->n_cells++] = c;
    c->reactor = r;
    c->value = value;
    c->update = update;
    c->func = func;
    c->callbacks = NULL;
    c->ids = 0;
    return c;
}

void noop(struct cell *input) {
    DEBUG(printf("Input update\n"));
    (void)input;
}

struct cell *create_input_cell(struct reactor *r, int initial_value) {
    DEBUG(printf("Creating input cell\n"));
    struct cell *c = create_cell(r, noop, NULL, initial_value);
    return c;
}

struct callback_data {
    struct callback_data *next;
    callback func;
    void *data;
    int id;
};

void run_callbacks(struct cell *c) {
    for(struct callback_data *p = c->callbacks; p != NULL; p = p->next ) {
        DEBUG(printf("Running callback %p: %d\n", (void *)c, p->id));
        p->func(p->data, c->value);
    }
}

void update_compute1(struct cell *c) {
    DEBUG(printf("Compute 1 update\n"));
    int new_value = ((compute1)c->func)(get_cell_value(c->inputs[0]));
    if( new_value == c->value)
        return;
    c->value = new_value;
    run_callbacks(c);
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *input,
        compute1 func) {
    DEBUG(printf("Creating compute1 cell \n"));
    struct cell *c = create_cell(r, update_compute1, (void *)func,
            func(get_cell_value(input)));
    c->inputs = calloc(sizeof(struct cell *), 1);
    c->inputs[0] = input;
    return c;
}

void update_compute2(struct cell *c) {
    DEBUG(printf("Compute 2 update\n"));
    int new_value = ((compute2)c->func)(get_cell_value(c->inputs[0]),
            get_cell_value(c->inputs[1]));
    if(new_value == c->value)
        return;
    c->value = new_value;
    run_callbacks(c);
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *input1,
        struct cell *input2, compute2 func) {
    DEBUG(printf("Creating compute2 cell\n"));
    struct cell *c = create_cell(r, update_compute2, (void *)func, 
            func(get_cell_value(input1), get_cell_value(input2)));
    c->inputs = calloc(sizeof(struct cell *), 2);
    c->inputs[0] = input1;
    c->inputs[1] = input2;
    return c;
}

int get_cell_value(struct cell *c) {
    DEBUG(printf("Getting cell value %p\n", (void *)c));
    return c->value;
}

void set_cell_value(struct cell *c, int new_value) {
    DEBUG(printf("Setting cell value %p: %d\n", (void *)c, new_value));
    if(new_value == c->value)
        return;
    c->value = new_value;
    run_callbacks(c);
    update_reactor(c->reactor);
}

void destroy_reactor(struct reactor *r) {
    DEBUG(printf("Destorying reactor %p\n", (void *)r));
    free(r);
}

callback_id add_callback(struct cell *c, void *args, callback func) {
    DEBUG(printf("Adding callback to %p: %d\n", (void *)c, c->ids));
    struct callback_data *state = malloc(sizeof(struct callback_data));
    state->func = func;
    state->data = args;
    state->id = c->ids++; 
    state->next = c->callbacks;
    c->callbacks = state;
    return state->id;
}

void remove_callback(struct cell *c, callback_id id) {
    struct callback_data *prev = NULL;
    DEBUG(printf("Removing callback from %p: %d\n", (void *)c, id));
    for(struct callback_data *data = c->callbacks;
            data != NULL;
            prev = data, data = data->next) {
        if(data->id == id) {
            if(prev == NULL)
                c->callbacks = data->next;
            else
                prev->next = data->next;
            return;
        }
    }
}
