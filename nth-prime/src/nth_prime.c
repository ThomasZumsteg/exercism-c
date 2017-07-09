#include "nth_prime.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

int n_primes;

typedef struct node {
    uint32_t val;
    struct node* next;
    struct node* prev;
} node;

void append(node **root, uint32_t value) {
    node *n = malloc(sizeof(node));
    n->val = value;
    if(*root == NULL) {
        n->next = n;
        n->prev = n;
        *root = n;
        n_primes = 0;
    } else {
        n->prev = (*root)->prev;
        n->next = (*root)->prev->next;
        (*root)->prev->next = n;
        (*root)->prev = n;
    } 
    n_primes++;
}

uint32_t get(node *root, int nth) {
    node *n = root;
    for(int i = 1; i < nth; i++)
        n = n->next;
    return n->val;
}

int prime(uint32_t num, node *primes) {
    for(node *n = primes; n->val * n->val <= num; n = n->next){
        if(num % n->val == 0)
            return 0;
    }
    return 1;
}

uint32_t nth(int n) {
    if(n <= 0) return 0;
    struct node *primes;
    append(&primes, 2);
    append(&primes, 3);
    for(uint32_t p = 5; n_primes < n; p+=2) {
        if(prime(p, primes))
            append(&primes, p);

    }
    return get(primes, n);
}

