#ifndef ALLERGIES_H
#define ALLERGIES_H

typedef enum {
   Allergen_Eggs = 0,
   Allergen_Peanuts,
   Allergen_Shellfish,
   Allergen_Strawberries,
   Allergen_Tomatoes,
   Allergen_Chocolate,
   Allergen_Pollen,
   Allergen_Cats,
   Allergen_Count
} Allergen_t;

typedef struct {
   int count;
   Allergen_t *allergens;
} Allergen_List_t;

void get_allergens(int score, Allergen_List_t *items);
int is_allergic_to(Allergen_t allergy, int score);

#endif
