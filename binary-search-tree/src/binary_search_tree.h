typedef struct node_t {
    struct node_t *left;
    struct node_t *right;
    int data;
} node_t;

node_t *build_tree(int[], int);
int *sorted_data(struct node_t *);
