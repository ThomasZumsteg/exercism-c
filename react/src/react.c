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
    int (* update)(void *inputs);
    void *inputs;
    callback_id ids;
    struct callback_data *callbacks;
};

struct reactor *create_reactor() {
    DEBUG(printf("Creating reactor\n"));
    struct reactor *r = malloc(sizeof(struct reactor));
    r->cells = NULL;
    return r;
}

int update_input(void *data) { return ((struct cell *)data)->value; }

struct cell *create_cell(struct reactor *r, int (*update)(void *), void *inputs) {
    struct cell *c = malloc(sizeof(struct cell));
    c->next = r->cells;
    r->cells = c;
    c->callbacks = NULL;
    c->ids = 0;
    if(update == NULL && inputs == NULL) {
        c->update = update_input;
        c->inputs = c;
    } else {
        c->update = update;
        c->inputs = inputs;
    }
    return c;
}

struct cell *create_input_cell(struct reactor *r, int initial_value) {
    DEBUG(printf("Creating input cell\n"));
    struct cell *c = create_cell(r, NULL, NULL);
    set_cell_value(c, initial_value);
    return c;
}

struct compute1_data { 
    compute1 func;
    struct cell *input;
};

int update_compute1(void *data) {
    DEBUG(printf("Compute 1 update\n"));
    struct compute1_data *cp1_data = (struct compute1_data *)data;
    return cp1_data->func(get_cell_value(cp1_data->input));
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *input,
        compute1 func) {
    DEBUG(printf("Creating compute1 cell \n"));
    struct compute1_data *data = malloc(sizeof(struct compute1_data));
    data->func = func;
    data->input = input;
    return create_cell(r, update_compute1, data);
}

struct compute2_data {
    compute2 func;
    struct cell *input1;
    struct cell *input2;
};

int update_compute2(void *data) {
    DEBUG(printf("Compute 2 update\n"));
    struct compute2_data *d = (struct compute2_data *)data;
    return d->func(get_cell_value(d->input1), get_cell_value(d->input2));
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *input1,
        struct cell *input2, compute2 func) {
    DEBUG(printf("Creating compute2 cell\n"));
    struct compute2_data *data = malloc(sizeof(struct compute2_data));
    data->func = func;
    data->input1 = input1;
    data->input2 = input2;

    return create_cell(r, update_compute2, data);
}

int get_cell_value(struct cell *c) {
    DEBUG(printf("Getting cell value %p\n", (void *)c));
    int new_value = c->update(c->inputs);
    if(new_value != c->value)
        set_cell_value(c, new_value);
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
