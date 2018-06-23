#define ERROR_VALUE -1

int steps(int start) {
    if( start <= 0 )
        return ERROR_VALUE;
    int step;
    for(step = 0; start != 1; step++)
        start = start % 2 == 0 ? start / 2 : start * 3 + 1;
    return step;
}
