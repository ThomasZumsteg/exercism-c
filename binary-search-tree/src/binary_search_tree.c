#include "binary_search_tree.h"
#include <stdlib.h>

#define MAX_SIZE 10

node_t *build_tree(int elements[], int n_elements) {
    struct node_t *root = NULL;
    struct node_t **tree_p;
    for(int e = 0; e < n_elements; e++) {
        tree_p = &root;
        while(*tree_p) {
            if((*tree_p)->data < elements[e])
                tree_p = &(*tree_p)->right;
            else
                tree_p = &(*tree_p)->left;
        }
        *tree_p = malloc(sizeof(struct node_t));
        (*tree_p)->left = NULL;
        (*tree_p)->right = NULL;
        (*tree_p)->data = elements[e];
    }
    return root;
}

int *sorted_data(struct node_t *tree) {
    int *result = calloc(sizeof(int), MAX_SIZE);
    int r = 0;
    node_t *queue[MAX_SIZE];
    int q = 0;
    int down = 1;
    queue[q] = tree;
    while(0 <= q) {
        node_t *node = queue[q];
        if(down) {
            if(node->left)
                queue[++q] = node->left;
            else
                down = 0;
        } else {
            q--;
            result[r++] = node->data;
            if(node->right) {
                down = 1;
                queue[++q] = node->right;
            } 
        }
    }
    return result;
}
