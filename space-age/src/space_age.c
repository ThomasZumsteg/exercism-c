#include "space_age.h"

unsigned long get_year_len(enum planet p) {
    switch(p) {
        case mercury: return 7600544;
        case venus: return 19414149;
        case earth: return 31557600;
        case mars: return 59354033;
        case jupiter: return 374355659;
        case saturn: return 929292363;
        case uranus: return 2651370019;
        case neptune: return 5200418560;
        default: return 0;
    }
}
 

double convert_planet_age(enum planet p, unsigned long int age) {
    return (double)age / get_year_len(p);
}
