#include "sublist.h"

comparison_result_t check_lists(int *list_to_compare, int *base_list,
        size_t list_size, size_t base_size) {

    if(list_size == 0)
        return base_size == 0 ? EQUAL : SUBLIST;

    comparison_result_t result = SUBLIST;
    if(base_size < list_size) {
        int *list_tmp = base_list;
        base_list = list_to_compare;
        list_to_compare = list_tmp;
        int size_tmp = base_size;
        base_size = list_size;
        list_size = size_tmp;
        result = SUPERLIST;
    } else if(base_size == list_size) {
        result = EQUAL;
    }
    for(size_t b = 0; b <= base_size - list_size; b++) {
        int contains = 1;
        for(size_t l = 0; l < list_size; l++) {
            if(base_list[b+l] != list_to_compare[l]) {
                contains = 0;
                break;
            }
        }
        if(contains == 1) {
            return result;
        }
    }
    return UNEQUAL;
}
