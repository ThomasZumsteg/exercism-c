#include "allergies.h"
#include <stdlib.h>
#include <stdio.h>

void get_allergens(int score, Allergen_List_t *items) {
    items->count = 0;
    items->allergens = malloc(sizeof(Allergen_t) * Allergen_Count);
    for(Allergen_t a = Allergen_Eggs; a < Allergen_Count; a++){
        if(is_allergic_to(a, score))
            items->allergens[items->count++] = a;

    }
}

int is_allergic_to(Allergen_t allergy, int score) {
    return 1 << allergy & score;
}
