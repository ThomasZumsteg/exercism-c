#ifndef SPACE_AGE_H
#define SPACE_AGE_H

enum planet {
    mercury = 0,
    venus,
    earth,
    mars,
    jupiter,
    saturn,
    uranus,
    neptune,
    max,
};

double convert_planet_age(enum planet p, unsigned long int age);

#endif
