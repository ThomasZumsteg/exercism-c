#include "triangle.h"
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return *(double *)a < *(double *)b;
}

Triangle_t *sort_sides(const Triangle_t *t) {
    Triangle_t *s = malloc(sizeof(Triangle_t));
    double sides[3] = { t->a, t->b, t->c };
    qsort(sides, 3, sizeof(double), compare);
    s->a = sides[0]; s->b = sides[1]; s->c = sides[2];
    return s;
}

int is_equilateral(const Triangle_t *t) {
    return t->a == t->b && t->b == t->c && 0 < t->a;
}

int is_isosceles(const Triangle_t *t) {
    Triangle_t *s = sort_sides(t);
    return s->c + s->b > s->a && (s->a == s->b || s->b == s->c);
}

int is_scalene(const Triangle_t *t) {
    Triangle_t *s = sort_sides(t);
    return s->c + s->b > s->a && !is_equilateral(s) && !is_isosceles(s);
}
