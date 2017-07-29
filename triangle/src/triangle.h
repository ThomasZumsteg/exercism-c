#ifndef TRIANGLE_H
#define TRIANGLE_H

typedef struct {
   double a;
   double b;
   double c;
} Triangle_t;

int is_equilateral(const Triangle_t *t);
int is_isosceles(const Triangle_t *t);
int is_scalene(const Triangle_t *t);

#endif
