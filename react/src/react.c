#include "react.h"
#include <stdlib.h>
#include <stdio.h>
#define DEBUG(x) x
#define MAX_CALLBACKS 10

struct dep {
    struct cell *source;
    struct cell *dest;
    struct dep *next;
};

struct reactor {
    struct dep *first;
    struct dep *last;
    void *func[MAX_CALLBACKS];
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

void update_compute1(struct cell *cell) {
    DEBUG(printf("Updating compute1 cell: %p\n", (void *)cell));
    compute1 func = (int (*)(int))cell->func;
    int input = get_cell_value(cell->inputs[0]);
    set_cell_value(cell, func(input));
}

void add_dependancy(struct reactor *r, struct cell *source, struct cell *dest) {
    struct dep *d = calloc(sizeof(struct dep), 1);
    DEBUG(printf("Adding dependancy %p -> %p\n", (void *)source, (void *)dest));
    d->source = source;
    d->dest = dest;
    if(r->first == NULL) {
        r->first = d;
        r->last = d;
    } else
        r->last->next = d;
    r->last = d;
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *input,
        compute1 func) {
    struct cell *cell = calloc(sizeof(struct cell),1);
    cell->func = (void *)func;
    cell->reactor = r;

    cell->inputs = calloc(sizeof(struct cell *), 1);
    cell->inputs[0] = input;
    add_dependancy(r, input, cell);

    cell->update = &update_compute1;
    cell->update(cell);

    return cell;
}

void update_compute2(struct cell *cell) {
    DEBUG(printf("Updating compute1 cell: %p\n", (void *)cell));
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
    add_dependancy(r, input1, cell);
    add_dependancy(r, input2, cell);

    cell->update = &update_compute2;
    cell->update(cell);

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
    for(struct dep *d = r->first; d != NULL; d = d->next) {
        if(d->source == c) {
            DEBUG(printf("Updating depenancy %p -> %p\n", (void *)d->source,
                    (void *)d->source));
            d->dest->update(d->dest);
        }
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
