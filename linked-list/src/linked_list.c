#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

struct list_item {
    ll_data_t data;
    struct list_item* next;
    struct list_item* prev;
};

struct list_item** new_list() {
    return calloc(sizeof(struct list_item*), 1);
}

void delete_list(struct list_item** list) { free(list); }

int is_list_empty(struct list_item** list) {
    return !(list && *list);
}

int push(struct list_item** list, ll_data_t data) {
    if(!list) return 0;
    struct list_item* item = calloc(sizeof(struct list_item), 1);
    item->data = data;
    if(*list) {
        item->prev = (*list)->prev;
        item->next = *list;
        (*list)->prev->next = item;
        (*list)->prev = item;
    } else {
        item->next = item;
        item->prev = item;
    }
    *list = item;
    return 1;
}

int unshift(struct list_item** list, ll_data_t data) {
    if(!list) return 0;
    if(*list) {
        list = &(*list)->prev;
    }
    return push(list, data);
}

ll_data_t pop(struct list_item** list) {
  struct list_item *item = (*list);
  *list = item->next;
  (*list)->prev = item->prev;
  (*list)->prev->next = *list;
  ll_data_t data = item->data;
  free(item);
  return data;
}

ll_data_t shift(struct list_item** list) {
    *list = (*list)->prev;
    ll_data_t data = pop(list);
    return data;
}
