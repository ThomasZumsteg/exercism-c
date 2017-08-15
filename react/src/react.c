#include "react.h"
#include <stdlib.h>
#include <stdio.h>
#define DEBUG(x) x

struct reactor {
    struct cell *cells;
};

struct cell {
    int value;
    struct cell *next;
    callback_id ids;
    struct callback_data *callbacks;
};

struct reactor *create_reactor() {
    DEBUG(printf("Creating reactor\n"));
    struct reactor *r = malloc(sizeof(struct reactor));
    r->cells = NULL;
    return r;
}

struct cell *create_cell(struct reactor *r, int value) {
    struct cell *c = malloc(sizeof(struct cell));
    c->next = r->cells;
    r->cells = c;
    c->value = value;
    c->callbacks = NULL;
    c->ids = 0;
    return c;
}

struct cell *create_input_cell(struct reactor *r, int initial_value) {
    DEBUG(printf("Creating input cell\n"));
    return create_cell(r, initial_value);
}

struct compute1_data { 
    compute1 func;
    struct cell *output;
};

void update_compute1(void *data, int value) {
    DEBUG(printf("Compute 1 update\n"));
    struct compute1_data *cp1_data = (struct compute1_data *)data;
    set_cell_value(cp1_data->output, cp1_data->func(value));
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *input,
        compute1 func) {
    DEBUG(printf("Creating compute1 cell \n"));
    struct compute1_data *data = malloc(sizeof(struct compute1_data));
    data->func = func;
    data->output = create_cell(r, func(get_cell_value(input)));
    add_callback(input, data, update_compute1);
    return data->output;;
}

struct compute2_data {
    compute2 func;
    struct cell *input;
    struct cell *output;
    int left;
};

void update_compute2(void *data, int value) {
    DEBUG(printf("Compute 2 update\n"));
    struct compute2_data *d = (struct compute2_data *)data;
    int right = get_cell_value(d->input);
    int left  = value;
    if(d->left != 0) {
        left = right;
        right = value;
    }
    set_cell_value(d->output, d->func(left, right)); 
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *input1,
        struct cell *input2, compute2 func) {
    DEBUG(printf("Creating compute2 cell\n"));
    struct cell *c = create_cell(r, 
            func(get_cell_value(input1), get_cell_value(input2)));
    struct compute2_data *left = malloc(sizeof(struct compute2_data));
    left->func = func;
    left->input = input2;
    left->output = c;
    left->left = 1;
    add_callback(input1, left, update_compute2);

    struct compute2_data *right = malloc(sizeof(struct compute2_data));
    right->func = func;
    right->input = input1;
    right->output = c;
    right->left = 0;
    add_callback(input2, right, update_compute2);

    return c;
}

int get_cell_value(struct cell *c) {
    DEBUG(printf("Getting cell value %p\n", (void *)c));
    return c->value;
}

struct callback_data {
    callback func;
    void *data;
    int id;
    struct callback_data *next;
};

void destroy_callback_data(struct callback_data *d) {
    DEBUG(printf("Destorying data %p\n", (void *)d));
    free(d);
}

void set_cell_value(struct cell *c, int new_value) {
    DEBUG(printf("Setting cell value %p: %d\n", (void *)c, new_value));
    if(new_value == c->value)
        return;
    c->value = new_value;
    for(struct callback_data *p = c->callbacks; p != NULL; p = p->next ) {
        DEBUG(printf("Running callback %p: %d\n", (void *)c, p->id));
        p->func(p->data, new_value);
    }
}

void destroy_cell(struct cell *c) {
    DEBUG(printf("Destorying cell %p\n", (void *)c));
    for(struct callback_data *d = c->callbacks; d != NULL; d = c->callbacks) {
        c->callbacks = d->next;
        destroy_callback_data(d);
    }
    free(c);
}

void destroy_reactor(struct reactor *r) {
    DEBUG(printf("Destorying reactor %p\n", (void *)r));
    for(struct cell *c = r->cells; c != NULL; c = r->cells) {
        r->cells = c->next;
        destroy_cell(c); 
    }
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
            destroy_callback_data(data);
            return;
        }
    }
}
