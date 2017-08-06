#include "react.h"
#include <stdlib.h>
#define MAX_REACTORS 10

typedef int (*func)(void *);

struct reactor {
    func *func; 
    int n_inputs;
    struct cell **inputs;
    struct cell *output;
};

struct cell {
    int value;
    struct reactor **reactors;
    int n_reactors;
};

struct reactor *create_reactor() {
    return malloc(sizeof(struct reactor));
}

struct cell *create_input_cell(struct reactor *r, int initial_value) {
    struct cell *c = malloc(sizeof(struct cell));
    c->value = initial_value;
    c->reactors = calloc(sizeof(struct reactor), MAX_REACTORS);
    c->n_reactors = 1;
    return c;
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *input,
        compute1 func) {
    struct cell *c = malloc(sizeof(struct cell));
    return c;
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *input1,
                                  struct cell *input2, compute2 func) {
    struct cell *c = malloc(sizeof(struct cell));
    return c;
}

int get_cell_value(struct cell *c) {
    return c->value;
}

void set_cell_value(struct cell *c, int new_value) {
    c->value = new_value;
    for(int r = 0; r < c->n_reactors; r++) {
        switch(r->output->n_inputs) {
            case 1:
}

void destroy_reactor(struct reactor *r) {
    free(r);
}

callback_id add_callback(struct cell *c, void *func, callback call) {

}

void remove_callback(struct cell *c, callback_id id) {
}
